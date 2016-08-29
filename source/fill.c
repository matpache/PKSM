/*
* This file is part of EventAssistant
* Copyright (C) 2016 Bernardo Giordano
*
* This software is provided 'as-is', 
* without any express or implied warranty. 
* In no event will the authors be held liable for any damages 
* arising from the use of this software.
*
* This code is subject to the following restrictions:
*
* 1) The origin of this software must not be misrepresented; 
* 2) You must not claim that you wrote the original software. 
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>
#include <string.h>

void filldatabase(char *database[]) {
	
	for (int j = 0; j < 27 * 76; j++)
		database[j] = ".";
	
    database[8] = "0008 - Lucky Egg";
	database[53] = "0053 - Nugget";
	database[54] = "0054 - Super Potions";
	database[55] = "0055 - Luxury Ball";
	database[56] = "0056 - Rare Candy";
	database[57] = "0057 - Master Ball";
	database[58] = "0058 - 12 Quick Balls";
	database[59] = "0059 - 100 Potions";
	database[60] = "0060 - 2 Master Balls";
	database[151] = "0151 - Scrap 5 Rare Candy";
	database[152] = "0152 - Scrap Masterball";
	database[157] = "0157 - Max Revive";
	database[158] = "0158 - Masterball";
	database[518] = "0518 - Heracronite";
	database[518] = "0518 - Pinsirite";
	database[527] = "0527 - 100 Potions";
	database[1022] = "1022 - 100 Potions";
	database[1057] = "1057 - 50 Quick Balls";
	database[1502] = "1502 - Quickballs";
	database[1511] = "1511 - Rare Candy";
	database[2048] = "2048 - Eon Ticket";
	
	database[1] = "0001 - Birthday Eeveelutions and Pikachu";
	database[2] = "0002 - CoroCoro Garchomp";
	database[3] = "0003 - PC Tokyo Bay Inkay";
	database[4] = "0004 - Nuketta Wobbuffet";
	database[11] = "0011 - Alternate Event Garchomp";
	database[12] = "0012 - Eevee House Sylveon";
	database[15] = "0015 - CoroCoro Charizard X/Y";
	database[17] = "0017 - Garchomp";
	database[19] = "0019 - PC Scizor";
	database[20] = "0020 - PC Gengar";
	database[21] = "0021 - Darkrai";
	database[22] = "0022 - Diancie";
	database[25] = "0025 - M-Gyarados";
	database[26] = "0026 - M-Scizor";
	database[27] = "0027 - M-Kangaskhan";
	database[28] = "0028 - M-Gengar";
	database[29] = "0029 - M-Tyranitar";
	database[30] = "0030 - M-Mawile";
	database[33] = "0033 - Mega Kick Pikachu";
	database[34] = "0034 - Shiny Jirachi";
	database[37] = "0037 - Surf and Sea Incense Pikachu";
	database[38] = "0038 - Surf and Air Balloon Pikachu";
	database[39] = "0039 - Surf and Comet Shard Pikachu";
	database[40] = "0040 - Surf and Focus Band Pikachu";
	database[41] = "0041 - Surf and Silk Scarf Pikachu";
	database[42] = "0042 - Heart Stamp Pikachu";
	database[43] = "0043 - Charizard X/Y";
	database[44] = "0044 - Shiny Gengar";
	database[45] = "0045 - Tretta Rotom";
	database[46] = "0046 - Darkrai";
	database[47] = "0047 - Diancie";
	database[48] = "0048 - Birthday Eevolutions and Pikachu";
	database[49] = "0049 - Shiny Gengar";
	database[50] = "0050 - Pokescrap Shaymin";
	database[51] = "0051 - Pokescrap Keldeo";
	database[52] = "0052 - Pokescrap Victini";
	database[61] = "0061 - Shiny Jirachi";
	database[62] = "0062 - SSB4 Greninja";
	database[63] = "0063 - PC Piplup";
	database[64] = "0064 - PC Froakie";
	database[65] = "0065 - Shiny Charizard";
	database[66] = "0066 - Shiny Pikachu";
	database[67] = "0067 - Extremespeed Linoone";
	database[71] = "0071 - Egg Bagon,Carvanha,Numel,Ralts,Swablu";
	database[78] = "0078 - Shiny Rayquaza";
	database[79] = "0079 - P-Cafe Pikachu";	
	database[81] = "0081 - Movie Arceus";
	database[82] = "0082 - Movie Legends HA";
	database[83] = "0083 - Movie Hoopa";
	database[86] = "0086 - Serena's Fennekin";
	database[88] = "0088 - CoroCoro Rayquaza";
	database[89] = "0089 - Spring 2015 Kangaskhan";
	database[90] = "0090 - SG Shiny Rayquaza";
	database[94] = "0094 - Hiroshima PC Shiny Gyarados";
	database[95] = "0095 - Hiroshima PC Magikarp";
	database[96] = "0096 - Pokelab Bulbasaur";
	database[97] = "0097 - Pokelab Charmander";
	database[98] = "0098 - Pokelab Squirtle";
	database[99] = "0099 - 7/11 Pikachu";
	database[100] = "0100 - 7/11 Pancham";
	database[101] = "0101 - 7/11 Lugia";
	database[102] = "0102 - 7/11 Latios";
	database[107] = "0107 - Yokohama 2015 Shiny Pikachu";
	database[108] = "0108 - Altair Jirachi (Tanabata 2015)";
	database[109] = "0109 - Satay King Pikachu";
	database[110] = "0110 - Manesh Hoopa";
	database[111] = "0111 - Shiny Xerneas, Yveltal";
	database[113] = "0113 - Zygarde";	
	database[114] = "0114 - Expo Charizard";
	database[115] = "0115 - Expo Machamp";
	database[116] = "0116 - Expo Smeargle";
	database[117] = "0117 - Expo Zoroark";	
	database[119] = "0119 - Nintendo HK Rayquaza";
	database[120] = "0120 - Universe Diancie";
	database[121] = "0121 - Birthday Eeveelutions and Pikachu";
	database[122] = "0122 - Halloween 2015 Pumpkaboo";
	database[127] = "0127 - Pokelab Chikorita";
	database[128] = "0128 - Pokelab Cyndaquil";
	database[129] = "0129 - Pokelab Totodile";
	database[130] = "0130 - WCS 2015 Shiny Tyranitar";
	database[131] = "0131 - PC Shiny Diancie";
	database[132] = "0132 - PC Altaria,Audino,Sableye,Lucario,Slowbro";
	database[133] = "0133 - PC Altaria,Audino,Sableye,Lucario,Slowbro";	
	database[134] = "0134 - PC Altaria,Audino,Sableye,Lucario,Slowbro";
	database[135] = "0135 - PC Altaria,Audino,Sableye,Lucario,Slowbro";
	database[136] = "0136 - PC Altaria,Audino,Sableye,Lucario,Slowbro";
	database[137] = "0137 - VC Mew";
	database[138] = "0138 - Happy Hour Pikachu";
	database[141] = "0141 - Repeat Halloween Gengar";
	database[145] = "0145 - HK Shiny Jirachi";
	database[146] = "0146 - SG Arceus";	
	database[147] = "0147 - Scrap Eevee";
	database[148] = "0148 - Scrap Articuno";
	database[149] = "0149 - Scrap Zapdos";
	database[150] = "0150 - Scrap Moltres";	
	database[153] = "0153 - Scrap Venusaur";	
	database[154] = "0154 - Scrap Charizard";
	database[155] = "0155 - Scrap Blastoise";
	database[156] = "0156 - Scrap Mewtwo";
	database[159] = "0159 - Jade Infernape";
	database[161] = "0161 - Movie Volcanion";
	database[162] = "0162 - 720 Poll Greninja";
	database[163] = "0163 - Surf and Fly Pikachu";
	database[164] = "0164 - PC Shiny Ho-Oh";
	database[165] = "0165 - Masuda's Psyduck";
	database[166] = "0166 - Bestow Pikachu";	
	database[167] = "0167 - Hyadain Landorus";	
	database[168] = "0168 - Chymia's Shiny Gardevoir";
	database[169] = "0169 - Jarvis's Gengar";
	database[170] = "0170 - P-Cafe Pikachu (SG)";
	database[173] = "0173 - HKTW VGC16 Shiny Mewtwo";
	database[175] = "0175 - HKTW Mew";
	database[501] = "0501 - Winter2013 Garchomp";
	database[502] = "0502 - Winter2013 Scizor";
	database[504] = "0504 - Magmar, Electabuzz";	
	database[510] = "0510 - Arash's Mamoswine";
	database[511] = "0511 - Paris Vivillon";	
	database[512] = "0512 - WORLD14 Aegislash";
	database[514] = "0514 - Tretta Wobbuffet";
	database[515] = "0515 - SUM2014 Heracross and Pinsir";
	database[516] = "0516 - Charizard X/Y";
	database[523] = "0523 - Halloween 2014 Pumpkaboo";
	database[524] = "0524 - Halloween Shiny Gengar";
	database[525] = "0525 - November Diancie";
	database[535] = "0535 - World Championships Pachirisu";
	database[536] = "0536 - Phantom Force Darkrai";
	database[537] = "0537 - Shiny Charizard";
	database[538] = "0538 - GS Dragonite";
	database[539] = "0539 - World15 Sharpedo";
	database[546] = "0546 - Hope Diancie";
	database[547] = "0547 - Galileo Rayquaza";
	database[551] = "0551 - Gamescom Aromatisse/Sableye";
	database[552] = "0552 - Gamescom Bouffalant/Malamar";
	database[553] = "0553 - Harry Hoopa";
	database[557] = "0557 - GF Mew";
	database[558] = "0558 - GF Celebi";
	database[559] = "0559 - GF Jirachi";
	database[560] = "0560 - GF Darkrai";
	database[561] = "0561 - GF Manaphy";
	database[562] = "0562 - GF Shaymin";
	database[563] = "0563 - GF Arceus";
	database[566] = "0566 - GF Genesect";
	database[569] = "0569 - Aldora Articuno";
	database[570] = "0570 - Aldora Zapdos";
	database[571] = "0571 - Aldora Moltres";
	database[574] = "0574 - Happy Meowth";
	database[576] = "0576 - Descartes/XYZ Xerneas";
	database[577] = "0577 - Descartes/XYZ Yveltal";
	database[578] = "0578 - Descartes/XYZ Zygarde";
	database[580] = "0580 - Screenpeekaz Shiny Machamp";
	database[586] = "0586 - Play! Mewtwo";
	database[588] = "0588 - Helen Volcanion";
	database[812] = "0812 - Christmas Stantler";
	database[1001] = "1001 - Eevee House Sylveon";
	database[1004] = "1004 - Olleh TV Charizard X/Y";
	database[1005] = "1005 - Alternate Event Garchomp";
	database[1006] = "1006 - WCS14K Heracross";
	database[1007] = "1007 - WCS14K Manectric";
	database[1008] = "1008 - WCS14K Tyranitar";
	database[1012] = "1012 - WCS14K Pinsir";
	database[1013] = "1013 - WCS14K Houndoom";
	database[1014] = "1014 - WCS14K Aggron";
	database[1015] = "1015 - Wishing Star Jirachi";
	database[1016] = "1016 - Shiny Gengar";
	database[1017] = "1017 - Movie Darkrai";
	database[1018] = "1018 - Movie Diancie";
	database[1019] = "1019 - Se Jun Park Pachirisu";
	database[1023] = "1023 - Guidebook Keldeo";
	database[1024] = "1024 - Guidebook Shaymin";	
	database[1025] = "1025 - Guidebook Mareep";
	database[1026] = "1026 - Extremespeed Linoone";
	database[1027] = "1027 - Shiny Charizard";
	database[1029] = "1029 - Shiny Rayquaza";
	database[1041] = "1041 - Water Tribe Manaphy";
	database[1042] = "1042 - Mega Battle 2015 Charizard";
	database[1043] = "1043 - Shiny Pikachu";
	database[1047] = "1047 - Movie Kyogre";
	database[1048] = "1048 - Movie Groudon";
	database[1049] = "1049 - Movie Dialga";
	database[1050] = "1050 - Movie Palkia";
	database[1051] = "1051 - Movie Giratina";
	database[1052] = "1052 - Movie Kyurem";
	database[1053] = "1053 - Movie Arceus";
	database[1054] = "1054 - Movie Hoopa";
	database[1055] = "1055 - Shiny Gyarados";
	database[1058] = "1058 - Gamefreak Mew (22796)";
	database[1060] = "1060 - XYZ Xerneas";
	database[1061] = "1061 - XYZ Yveltal";
	database[1062] = "1062 - Korean Premiere XYZ Zygarde";
	database[1064] = "1064 - XYZ Zygarde";		
	database[1065] = "1065 - KOR HA Articuno";
	database[1066] = "1066 - KOR HA Zapdos";
	database[1067] = "1067 - KOR HA Moltres";
	database[1068] = "1068 - KOR HA Mewtwo";
	database[1070] = "1070 - KOR Naminori Pikachu";
	database[1501] = "1501 - HA Torchic";
	database[1503] = "1503 - Fancy Vivillon";
	database[1504] = "1504 - Shiny Beldum";
	database[1505] = "1505 - HA Serperior";
	database[1506] = "1506 - HA Emboar";
	database[1507] = "1507 - HA Samurott";
	database[1508] = "1508 - PGL Tyrunt";
	database[1509] = "1509 - PGL Amaura";
	database[1510] = "1510 - PGL Pikachu";
	database[1512] = "1512 - PGL Delibird";
	database[1513] = "1513 - PGL Dragonite";
	database[1514] = "1514 - PGL Miltank";
	database[1515] = "1515 - PGL Garchomp";
}