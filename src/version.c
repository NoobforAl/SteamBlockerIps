#include "version.h"
#include "log.h"

void print_banner(void)
{
    fprintf(stderr,
            "\n"
            "███████╗██████╗     ██╗██████╗ ███████╗\n"
            "██╔════╝██╔══██╗    ██║██╔══██╗██╔════╝\n"
            "███████╗██████╔╝    ██║██████╔╝███████╗\n"
            "╚════██║██╔══██╗    ██║██╔═══╝ ╚════██║\n"
            "███████║██████╔╝    ██║██║     ███████║\n"
            "╚══════╝╚═════╝     ╚═╝╚═╝     ╚══════╝\n"
            "%s Steam Blocker Ips server game! %s \n"
            " Version: %s \n\n",
            GREEN, RESET, VERSION);
}

void print_help(void)
{
    fprintf(stderr,
            "Usage: srblock disable [args(Country first symbol) ...]\n"
            "Usage: srblock enable\n"
            "\n"
            "   add srblock in firewall system\n"
            "   enable: remove ips from firewall\n"
            "   disable: add ips to firewall\n"
            "   country symobl list:\n"
            "      ams -- Amsterdam (Netherlands)\n"
            "      atl -- Atlanta (Georgia)\n"
            "      bom -- Mumbai (India)\n"
            "      can -- Perfect World Guangdong 2 (China)\n"
            "      ctu -- Alibaba Cloud Chengdu (China)\n"
            "      dfw -- Dallas (Texas)\n"
            "      dxb -- Dubai (United Arab Emirates)\n"
            "      eat -- Moses Lake (Washington)\n"
            "      eze -- Buenos Aires (Argentina)\n"
            "      fra -- Frankfurt (Germany)\n"
            "      gru -- Sao Paulo (Brazil)\n"
            "      hel -- Helsinki (Finland)\n"
            "      hkg -- Hong Kong\n"
            "      iad -- Sterling (Virginia)\n"
            "      jfk -- New York\n"
            "      jnb -- Johannesburg (South Africa)\n"
            "      lax -- Los Angeles (California)\n"
            "      lhr -- London (England)\n"
            "      lim -- Lima (Peru)\n"
            "      maa -- Chennai (India)\n"
            "      mad -- Madrid (Spain)\n"
            "      ord -- Chicago (Illinois)\n"
            "      par -- Paris (France)\n"
            "      pwg -- Perfect World Guangdong 1 (China)\n"
            "      pwj -- Perfect World Tianjin (China)\n"
            "      pwu -- Perfect World Hebei (China)\n"
            "      pww -- Perfect World Wuhan (China)\n"
            "      pwz -- Perfect World Zhejiang (China)\n"
            "      scl -- Santiago (Chile)\n"
            "      sea -- Seattle (Washington)\n"
            "      seo -- Seoul (South Korea)\n"
            "      sgp -- Singapore\n"
            "      sha -- Perfect World Shanghai (China)\n"
            "      shb -- Perfect World (sha-4) Backbone (Shanghai, China)\n"
            "      sto -- Stockholm - Kista (Sweden)\n"
            "      syd -- Sydney (Australia)\n"
            "      tsn -- Perfect World Tianjin (China)\n"
            "      tyo -- Tokyo Koto City (Japan)\n"
            "      vie -- Vienna (Austria)\n"
            "      waw -- Warsaw (Poland)\n"
            "      bom2 -- Mumbai (India)\n"
            "      sto2 -- Stockholm - Bromma (Sweden)\n"
            "      canm -- Perfect World Guangdong 2 - Mobile (China)\n"
            "      ctum -- Alibaba Cloud Chengdu - Mobile (China)\n"
            "      sham -- Perfect World Shanghai - Mobile (China)\n"
            "      tsnm -- Perfect World Tianjin - Mobile (China)\n"
            "      cant -- Perfect World Guangdong 2 - Telecom (China)\n"
            "      ctut -- Alibaba Cloud Chengdu - Telecom (China)\n"
            "      shat -- Perfect World Shanghai - Telecom (China)\n"
            "      tsnt -- Perfect World Tianjin - Telecom (China)\n"
            "      canu -- Perfect World Guangdong 2 - Unicom (China)\n"
            "      ctuu -- Alibaba Cloud Chengdu - Unicom (China)\n"
            "      shau -- Perfect World Shanghai - Unicom (China)\n"
            "      tsnu -- Perfect World Tianjin - Unicom (China)\n"
            "example: srblock disable tsnu shau  \n");
}
