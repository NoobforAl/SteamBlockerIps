#!/bin/python3

import json
import logging
import subprocess as sp
import requests as req  # pip install requests

# import types
from logging import Logger

DEFAULT_API_REQ: str = "https://api.steampowered.com/ISteamApps/GetSDRConfig/v1/?appid=730"
DATA_JSON_FILE: str = "./data.json"
BLOCK_IPS_FILE: str = "./blockips.txt"

log: Logger = logging.getLogger("SB Ips Test")
log.setLevel(logging.DEBUG)

formatter = logging.Formatter(
    '%(asctime)s - %(name)s - %(levelname)s - %(message)s')
stream_handler = logging.StreamHandler()
stream_handler.setFormatter(formatter)

log.addHandler(stream_handler)


def run_command_and_get_result(command: str) -> tuple[int, str]:
    process = sp.Popen([command],
                       stdout=sp.PIPE,
                       stderr=sp.PIPE,
                       shell=True)
    rc: int = process.wait()
    if rc != 0:
        log.error(f"normal run '{command}' exit with exit code: {rc}")
        return rc, ""

    stdout, _ = process.communicate()
    ips_ufw = stdout.decode()

    return rc, ips_ufw


def get_ips_from_file(symbol: str) -> list[str]:
    try:
        data_json: dict = {}
        with open(DATA_JSON_FILE, 'r') as f:
            data_json = json.load(f)

        bom_ips: list[str] = []
        for relay in data_json["pops"][symbol]["relays"]:
            bom_ips.append(relay["ipv4"])
        return bom_ips

    except Exception as err:
        log.error(err)
        return []


def enable_ufw() -> None:
    rc: int = sp.call(["sudo ufw enable"], shell=True)
    if rc != 0:
        log.error(f"can't enable ufw exit code: {rc}")
        exit(1)


def build_app() -> None:
    rc: int = sp.call(["make build"], shell=True)
    if rc != 0:
        log.error(f"can't build app exit code: {rc}")
        exit(1)


def run_app():
    rc, _ = run_command_and_get_result("./app disable bom")
    if rc != 0:
        exit(1)


def check_data_received_is_equal() -> None:
    with req.get(DEFAULT_API_REQ) as res:
        if res.status_code != 200:
            log.error(f"error to request status code: {res.status_code}")
            exit(1)

        json_data_text: str = res.text
        with open(DATA_JSON_FILE, 'r') as f:
            if f.read() != json_data_text:
                log.error("not equal data!")
                exit(1)


def check_true_blocks_ips() -> None:
    bom_ips: list[str] = get_ips_from_file("bom")

    blockips_from_file: list[str] = []
    with open(BLOCK_IPS_FILE, 'r') as f:
        blockips_from_file = f.read().split("\n")

    for ip in bom_ips:
        if ip not in blockips_from_file:
            log.error(f"not found this {ip} ip in blocked ips file!")
            exit(1)

    rc, ips_ufw = run_command_and_get_result("sudo ufw status")
    if rc != 0:
        exit(1)

    for ip in bom_ips:
        if ips_ufw.find(ip) == -1:
            log.error(f"not found this {ip} ip in ufw!")
            exit(1)


def check_remove_ips_in_firewall() -> None:
    rc, _ = run_command_and_get_result("./app enable")
    if rc != 0:
        exit(1)

    bom_ips: list[str] = get_ips_from_file("bom")
    rc, ips_ufw = run_command_and_get_result("sudo ufw status")
    if rc != 0:
        exit(1)

    for ip in bom_ips:
        if ips_ufw.find(ip) != -1:
            log.error(f"found this {ip} ip in ufw! enable ips not work!")
            exit(1)


def remove_build_files() -> None:
    rc, _ = run_command_and_get_result("make clean")
    if rc != 0:
        exit(1)


def main() -> None:
    try:
        log.info("Build app and run!")
        enable_ufw()
        build_app()
        run_app()

        log.info("check data received with data.json is equal !")
        check_data_received_is_equal()

        log.info("check true blocks ips!")
        check_true_blocks_ips()

        log.info("check true remove ips in firewall!")
        check_remove_ips_in_firewall()

        log.info("All test is ok!")

    finally:
        log.warning("cleaning data after test!")
        remove_build_files()


if __name__ == "__main__":
    main()
