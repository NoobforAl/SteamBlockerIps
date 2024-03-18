# SteamBlockerIps

Simple Ip game server blocker!

## Requirements

For build:

- gcc
- make
- curl
- curl lib
- cjson lib
- ufw ( for linux user )
- upx

For test:

- python3.12
- requests lib ( pip install requests )
- docker

## How build

> make build

for build and run:

> make

## How usage

Run normal app see help:
> app

```txt

███████╗██████╗     ██╗██████╗ ███████╗
██╔════╝██╔══██╗    ██║██╔══██╗██╔════╝
███████╗██████╔╝    ██║██████╔╝███████╗
╚════██║██╔══██╗    ██║██╔═══╝ ╚════██║
███████║██████╔╝    ██║██║     ███████║
╚══════╝╚═════╝     ╚═╝╚═╝     ╚══════╝
 Steam Blocker Ips server game!  
 Version: 0.1.0 

Usage: srblock disable [args(Country first symbol) ...]
Usage: srblock enable

   add srblock in firewall system
   enable: remove ips from firewall
   disable: add ips to firewall
   country symobl list:
      ams -- Amsterdam (Netherlands)
      atl -- Atlanta (Georgia)
      bom -- Mumbai (India)
      can -- Perfect World Guangdong 2 (China)
      ctu -- Alibaba Cloud Chengdu (China)
      dfw -- Dallas (Texas)
      dxb -- Dubai (United Arab Emirates)
      eat -- Moses Lake (Washington)
      eze -- Buenos Aires (Argentina)
      fra -- Frankfurt (Germany)
      gru -- Sao Paulo (Brazil)
      hel -- Helsinki (Finland)
      hkg -- Hong Kong
      iad -- Sterling (Virginia)
      jfk -- New York
      jnb -- Johannesburg (South Africa)
      lax -- Los Angeles (California)
      lhr -- London (England)
      lim -- Lima (Peru)
      maa -- Chennai (India)
      mad -- Madrid (Spain)
      ord -- Chicago (Illinois)
      par -- Paris (France)
      pwg -- Perfect World Guangdong 1 (China)
      pwj -- Perfect World Tianjin (China)
      pwu -- Perfect World Hebei (China)
      pww -- Perfect World Wuhan (China)
      pwz -- Perfect World Zhejiang (China)
      scl -- Santiago (Chile)
      sea -- Seattle (Washington)
      seo -- Seoul (South Korea)
      sgp -- Singapore
      sha -- Perfect World Shanghai (China)
      shb -- Perfect World (sha-4) Backbone (Shanghai, China)
      sto -- Stockholm - Kista (Sweden)
      syd -- Sydney (Australia)
      tsn -- Perfect World Tianjin (China)
      tyo -- Tokyo Koto City (Japan)
      vie -- Vienna (Austria)
      waw -- Warsaw (Poland)
      bom2 -- Mumbai (India)
      sto2 -- Stockholm - Bromma (Sweden)
      canm -- Perfect World Guangdong 2 - Mobile (China)
      ctum -- Alibaba Cloud Chengdu - Mobile (China)
      sham -- Perfect World Shanghai - Mobile (China)
      tsnm -- Perfect World Tianjin - Mobile (China)
      cant -- Perfect World Guangdong 2 - Telecom (China)
      ctut -- Alibaba Cloud Chengdu - Telecom (China)
      shat -- Perfect World Shanghai - Telecom (China)
      tsnt -- Perfect World Tianjin - Telecom (China)
      canu -- Perfect World Guangdong 2 - Unicom (China)
      ctuu -- Alibaba Cloud Chengdu - Unicom (China)
      shau -- Perfect World Shanghai - Unicom (China)
      tsnu -- Perfect World Tianjin - Unicom (China)
example: srblock disable tsnu shau  
```

Note: after run, don't remove block_ips.txt, all ips blocked in here!

### TODOS

- [ ] Support windows
- [ ] Support Other Game
