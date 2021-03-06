/*
* This file is part of PKSM
* Copyright (C) 2016 Bernardo Giordano
*
* Credits to SlashCash & PCHex++ for lots of functions redistributed in this software.
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

#include <3ds.h>
#include <string.h>
#include "graphic.h"
#include "editor.h"
#include "util.h"
#include "save.h"

/* ************************ local variables ************************ */

const int SMWC7FLAGPOS = 0x65C00;
const int SMWC7POS = 0x65C00 + 0x100;
const int ORASWC6FLAGPOS = 0x1CC00;
const int ORASWC6POS = 0x1CD00;
const int XYWC6FLAGPOS = 0x1BC00;
const int XYWC6POS = 0x1BD00;
const int DPPGTFLAGPOS = 0xA6D0;
const int DPPGTPOS = 0xA7FC;
const int PTPGTFLAGPOS = 0xB4C0;
const int PTPGTPOS = 0xB5C0;
const int HGSSPGTFLAGPOS = 0x9D3C;
const int HGSSPGTPOS = 0x9E3C;
const int EONFLAGPOS = 0x319B8;
const int LANGUAGEPOS = 0x1402D;
const int MONEYPOS = 0x4208;
const int BADGEPOS = 0x420C;
const int TMSTARTPOS = 0xBC0;
const int OFFSET = 0x5400;
const int MOVEPOS = 0x5A;
const int EGGMOVEPOS = 0x6A;
const int EVPOS = 0x1E;
const int PIDPOS = 0x18;
const int IVPOS = 0x74;
const int OTIDPOS = 0x0C;
const int SOTIDPOS = 0x0E;
const int OTNAMELENGTH = 0x17;
const int OTNAMEPOS = 0xB0;
const int NICKNAMEPOS = 0x40;
const int POKEDEXNUMBERPOS = 0x08;
const int NATUREPOS = 0x1C;
const int ITEMPOS = 0x0A;
const int EXPPOINTPOS = 0x10;
const int ABILITYPOS = 0x14;
const int ABILITYNUMPOS = 0x15;
const int GENDERPOS = 0x1D;
const int POKERUS = 0x11;
const int PGFSTARTPOS = 0x1C800;
const int BWSEEDPOS = 0x1D290;

u32 expTable[100][6] = {
  {0, 0, 0, 0, 0, 0},
  {8, 15, 4, 9, 6, 10},
  {27, 52, 13, 57, 21, 33},
  {64, 122, 32, 96, 51, 80},
  {125, 237, 65, 135, 100, 156},
  {216, 406, 112, 179, 172, 270},
  {343, 637, 178, 236, 274, 428},
  {512, 942, 276, 314, 409, 640},
  {729, 1326, 393, 419, 583, 911},
  {1000, 1800, 540, 560, 800, 1250},
  {1331, 2369, 745, 742, 1064, 1663},
  {1728, 3041, 967, 973, 1382, 2160},
  {2197, 3822, 1230, 1261, 1757, 2746},
  {2744, 4719, 1591, 1612, 2195, 3430},
  {3375, 5737, 1957, 2035, 2700, 4218},
  {4096, 6881, 2457, 2535, 3276, 5120},
  {4913, 8155, 3046, 3120, 3930, 6141},
  {5832, 9564, 3732, 3798, 4665, 7290},
  {6859, 11111, 4526, 4575, 5487, 8573},
  {8000, 12800, 5440, 5460, 6400, 10000},
  {9261, 14632, 6482, 6458, 7408, 11576},
  {10648, 16610, 7666, 7577, 8518, 13310},
  {12167, 18737, 9003, 8825, 9733, 15208},
  {13824, 21012, 10506, 10208, 11059, 17280},
  {15625, 23437, 12187, 11735, 12500, 19531},
  {17576, 26012, 14060, 13411, 14060, 21970},
  {19683, 28737, 16140, 15244, 15746, 24603},
  {21952, 31610, 18439, 17242, 17561, 27440},
  {24389, 34632, 20974, 19411, 19511, 30486},
  {27000, 37800, 23760, 21760, 21600, 33750},
  {29791, 41111, 26811, 24294, 23832, 37238},
  {32768, 44564, 30146, 27021, 26214, 40960},
  {35937, 48155, 33780, 29949, 28749, 44921},
  {39304, 51881, 37731, 33084, 31443, 49130},
  {42875, 55737, 42017, 36435, 34300, 53593},
  {46656, 59719, 46656, 40007, 37324, 58320},
  {50653, 63822, 50653, 43808, 40522, 63316},
  {54872, 68041, 55969, 47846, 43897, 68590},
  {59319, 72369, 60505, 52127, 47455, 74148},
  {64000, 76800, 66560, 56660, 51200, 80000},
  {68921, 81326, 71677, 61450, 55136, 86151},
  {74088, 85942, 78533, 66505, 59270, 92610},
  {79507, 90637, 84277, 71833, 63605, 99383},
  {85184, 95406, 91998, 77440, 68147, 106480},
  {91125, 100237, 98415, 83335, 72900, 113906},
  {97336, 105122, 107069, 89523, 77868, 121670},
  {103823, 110052, 114205, 96012, 83058, 129778},
  {110592, 115015, 123863, 102810, 88473, 138240},
  {117649, 120001, 131766, 109923, 94119, 147061},
  {125000, 125000, 142500, 117360, 100000, 156250},
  {132651, 131324, 151222, 125126, 106120, 165813},
  {140608, 137795, 163105, 133229, 112486, 175760},
  {148877, 144410, 172697, 141677, 119101, 186096},
  {157464, 151165, 185807, 150476, 125971, 196830},
  {166375, 158056, 196322, 159635, 133100, 207968},
  {175616, 165079, 210739, 169159, 140492, 219520},
  {185193, 172229, 222231, 179056, 148154, 231491},
  {195112, 179503, 238036, 189334, 156089, 243890},
  {205379, 186894, 250562, 199999, 164303, 256723},
  {216000, 194400, 267840, 211060, 172800, 270000},
  {226981, 202013, 281456, 222522, 181584, 283726},
  {238328, 209728, 300293, 234393, 190662, 297910},
  {250047, 217540, 315059, 246681, 200037, 312558},
  {262144, 225443, 335544, 259392, 209715, 327680},
  {274625, 233431, 351520, 272535, 219700, 343281},
  {287496, 241496, 373744, 286115, 229996, 359370},
  {300763, 249633, 390991, 300140, 240610, 375953},
  {314432, 257834, 415050, 314618, 251545, 393040},
  {328509, 267406, 433631, 329555, 262807, 410636},
  {343000, 276458, 459620, 344960, 274400, 428750},
  {357911, 286328, 479600, 360838, 286328, 447388},
  {373248, 296358, 507617, 377197, 298598, 466560},
  {389017, 305767, 529063, 394045, 311213, 486271},
  {405224, 316074, 559209, 411388, 324179, 506530},
  {421875, 326531, 582187, 429235, 337500, 527343},
  {438976, 336255, 614566, 447591, 351180, 548720},
  {456533, 346965, 639146, 466464, 365226, 570666},
  {474552, 357812, 673863, 485862, 379641, 593190},
  {493039, 367807, 700115, 505791, 394431, 616298},
  {512000, 378880, 737280, 526260, 409600, 640000},
  {531441, 390077, 765275, 547274, 425152, 664301},
  {551368, 400293, 804997, 568841, 441094, 689210},
  {571787, 411686, 834809, 590969, 457429, 714733},
  {592704, 423190, 877201, 613664, 474163, 740880},
  {614125, 433572, 908905, 636935, 491300, 767656},
  {636056, 445239, 954084, 660787, 508844, 795070},
  {658503, 457001, 987754, 685228, 526802, 823128},
  {681472, 467489, 1035837, 710266, 545177, 851840},
  {704969, 479378, 1071552, 735907, 563975, 881211},
  {729000, 491346, 1122660, 762160, 583200, 911250},
  {753571, 501878, 1160499, 789030, 602856, 941963},
  {778688, 513934, 1214753, 816525, 622950, 973360},
  {804357, 526049, 1254796, 844653, 643485, 1005446},
  {830584, 536557, 1312322, 873420, 664467, 1038230},
  {857375, 548720, 1354652, 902835, 685900, 1071718},
  {884736, 560922, 1415577, 932903, 707788, 1105920},
  {912673, 571333, 1460276, 963632, 730138, 1140841},
  {941192, 583539, 1524731, 995030, 752953, 1176490},
  {970299, 591882, 1571884, 1027103, 776239, 1212873},
  {1000000, 600000, 1640000, 1059860, 800000, 1250000}
};

/* ************************ utilities ************************ */

u32 seedStep(const u32 seed) {
    return (seed * 0x41C64E6D + 0x00006073) & 0xFFFFFFFF;
}

u32 LCRNG(u32 seed) {
	return seed * 0x41C64E6D + 0x00006073;
}

void shuffleArray(u8* pkmn, const u32 encryptionkey) {
    const int BLOCKLENGHT = 56;

    u8 seed = (((encryptionkey & 0x3E000) >> 0xD) % 24);

    int aloc[24] = { 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3 };
    int bloc[24] = { 1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2 };
    int cloc[24] = { 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1 };
    int dloc[24] = { 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0 };
    int ord[4] = {aloc[seed], bloc[seed], cloc[seed], dloc[seed]};

    char pkmncpy[PKMNLENGTH];
    char tmp[BLOCKLENGHT];

    memcpy(&pkmncpy, pkmn, PKMNLENGTH);

    for (int i = 0; i < 4; i++) {
        memcpy(tmp, pkmncpy + 8 + BLOCKLENGHT * ord[i], BLOCKLENGHT);
        memcpy(pkmn + 8 + BLOCKLENGHT * i, tmp, BLOCKLENGHT);
    }
}

void decryptPkmn(u8* pkmn) {
    const int ENCRYPTIONKEYPOS = 0x0;
    const int ENCRYPTIONKEYLENGHT = 4;
    const int CRYPTEDAREAPOS = 0x08;

    u32 encryptionkey;
    memcpy(&encryptionkey, &pkmn[ENCRYPTIONKEYPOS], ENCRYPTIONKEYLENGHT);
    u32 seed = encryptionkey;

    u16 temp;
    for (int i = CRYPTEDAREAPOS; i < PKMNLENGTH; i += 2) {
        memcpy(&temp, &pkmn[i], 2);
        temp ^= (seedStep(seed) >> 16);
        seed = seedStep(seed);
        memcpy(&pkmn[i], &temp, 2);
    }

    shuffleArray(pkmn, encryptionkey);
}

int getPkmnAddress(const int boxnumber, const int indexnumber, int game) {
    int boxpos = 0;
    if (game == GAME_X || game == GAME_Y)
		boxpos = 0x27A00 - OFFSET;

    if (game == GAME_OR || game == GAME_AS)
		boxpos = 0x38400 - OFFSET;

	if (game == GAME_SUN || game == GAME_MOON)
		boxpos = 0x04E00;

    const int PKMNNUM = 30;

	return boxpos + (PKMNLENGTH * PKMNNUM * boxnumber) + (indexnumber * PKMNLENGTH);
}

void calculatePKMNChecksum(u8* data) {
    u16 chk = 0;

    for (int i = 8; i < PKMNLENGTH; i += 2)
        chk += *(u16*)(data + i);

    memcpy(data + 6, &chk, 2);
}

void encryptPkmn(u8* pkmn) {
    const int ENCRYPTIONKEYPOS = 0x0;
    const int ENCRYPTIONKEYLENGHT = 4;
    const int CRYPTEDAREAPOS = 0x08;

    u32 encryptionkey;
    memcpy(&encryptionkey, &pkmn[ENCRYPTIONKEYPOS], ENCRYPTIONKEYLENGHT);
    u32 seed = encryptionkey;

    for(int i = 0; i < 11; i++)
        shuffleArray(pkmn, encryptionkey);

    u16 temp;
    for(int i = CRYPTEDAREAPOS; i < PKMNLENGTH; i += 2) {
        memcpy(&temp, &pkmn[i], 2);
        temp ^= (seedStep(seed) >> 16);
        seed = seedStep(seed);
        memcpy(&pkmn[i], &temp, 2);
    }
}

void getPkmn(u8* mainbuf, const int boxnumber, const int indexnumber, u8* pkmn, int game) {
    memcpy(pkmn, &mainbuf[getPkmnAddress(boxnumber, indexnumber, game)], PKMNLENGTH);
    decryptPkmn(pkmn);
}

void setPkmn(u8* mainbuf, const int boxnumber, const int indexnumber, u8* pkmn, int game) {
    calculatePKMNChecksum(pkmn);
    encryptPkmn(pkmn);

    memcpy(&mainbuf[getPkmnAddress(boxnumber, indexnumber, game)], pkmn, PKMNLENGTH);
}

bool isShiny(u8* pkmn) {
    u16 trainersv = (getOTID(pkmn) ^ getSOTID(pkmn)) >> 4;
    u16 pkmnv = ((getPID(pkmn) >> 16) ^ (getPID(pkmn) & 0xFFFF)) >> 4;

    if (trainersv == pkmnv) return true;
    else return false;
}

void rerollPID(u8* pkmn) {
    srand(getPID(pkmn));
    u32 pidbuffer = rand();

    memcpy(&pkmn[PIDPOS], &pidbuffer, PIDLENGTH);
}

bool isEgg(u8* pkmn) {
    u32 eggbuffer;
    memcpy(&eggbuffer, &pkmn[IVPOS], IVLENGTH);
    eggbuffer = eggbuffer >> 30;
    eggbuffer = eggbuffer & 0x1;
    if (eggbuffer == 1) 
        return true;
    
    else return false;
}

/* ************************ get ************************ */

u16 getEggMove(u8 *pkmn, const int nmove) {
    u16 eggmovebuffer[4];
    memcpy(&eggmovebuffer, &pkmn[EGGMOVEPOS], EGGMOVELENGTH*4);
    
    return eggmovebuffer[nmove];
}

u8 getForm(u8* pkmn) {
    u8 bufferform;
    memcpy(&bufferform, &pkmn[GENDERPOS], GENDERLENGTH);
    bufferform = (bufferform >> 3);
    return bufferform;
}

u16 getStat(u8* pkmn, const int stat) {
    u16 tempspecies = getPokedexNumber(pkmn);
    if (getForm(pkmn))
		memcpy(&tempspecies, &personal.pkmData[getPokedexNumber(pkmn)][0x1C], 2);

    u8 mult = 10;
    u16 final;
    u8 basestat = 1;
    if (stat == 0) basestat = personal.pkmData[tempspecies][0x0];
    if (stat == 1) basestat = personal.pkmData[tempspecies][0x1];
    if (stat == 2) basestat = personal.pkmData[tempspecies][0x2];
    if (stat == 3) basestat = personal.pkmData[tempspecies][0x3];
    if (stat == 4) basestat = personal.pkmData[tempspecies][0x4];
    if (stat == 5) basestat = personal.pkmData[tempspecies][0x5];

    if (stat == 0)
        final = 10 + ((2 * basestat) + getIV(pkmn, stat) + getEV(pkmn, stat) / 4 + 100) * getLevel(pkmn) / 100;
    else
        final = 5 + (2 * basestat + getIV(pkmn, stat) + getEV(pkmn, stat) / 4) * getLevel(pkmn) / 100;

    if (getNature(pkmn) / 5 + 1 == stat)
        mult++;
    if (getNature(pkmn) % 5 + 1 == stat)
        mult--;

    final = final * mult / 10;
    return final;
}

u8 getAbility(u8* pkmn) {
    u8 abilitybuffer;
    memcpy(&abilitybuffer, &pkmn[ABILITYPOS], ABILITYLENGTH);
	return abilitybuffer;
}

bool isInfected (u8* pkmn) {
	u8 pkrs;
	memcpy(&pkrs, &pkmn[0x2B], 1);
	pkrs = pkrs >> 4;
	return pkrs > 0;
}

char *getOT(u8* pkmn, char* dst) {
	u16 src[OTNAMELENGTH];
	memcpy(src, &pkmn[OTNAMEPOS], OTNAMELENGTH);
	int cnt = 0;

	while (src[cnt] && cnt < 24) {
		dst[cnt] = src[cnt];
		cnt += 1;
	}
	dst[cnt] = 0;
	return dst;
}

char *getNickname(u8* pkmn, char* dst) {
	u16 src[NICKNAMELENGTH];
	memcpy(src, &pkmn[NICKNAMEPOS], NICKNAMELENGTH);
	int cnt = 0;

	while (src[cnt] && cnt < NICKNAMELENGTH) {
		dst[cnt] = src[cnt];
		cnt += 1;
	}
	dst[cnt] = 0;
	return dst;
}

u8 getLevel(u8* pkmn) {
	u32 exp;
	u8 xpType = personal.pkmData[getPokedexNumber(pkmn)][0x15];
	u8 iterLevel = 1;
	memcpy(&exp, &pkmn[EXPPOINTPOS], EXPPOINTLENGTH);

	while (iterLevel < 100 && exp >= expTable[iterLevel][xpType])
		iterLevel++;

	return iterLevel;
}

u16 getMove(u8* pkmn, int nmove) {
    u16 movebuffer[4];
    memcpy(&movebuffer, &pkmn[MOVEPOS], MOVELENGTH*4);

    return movebuffer[nmove];
}

u16 getItem(u8* pkmn) {
    u16 itembuffer;
    memcpy(&itembuffer, &pkmn[ITEMPOS], ITEMLENGTH);

    return itembuffer;
}

u8 getHPType(u8* pkmn) {
    return 15 * ((getIV(pkmn, 0)& 1) + 2 * (getIV(pkmn, 1) & 1) + 4 * (getIV(pkmn, 2) & 1) + 8 * (getIV(pkmn, 3) & 1) + 16 * (getIV(pkmn, 4) & 1) + 32 * (getIV(pkmn, 5) & 1)) / 63;
}

u16 getOTID(u8* pkmn) {
    u16 otidbuffer;
    memcpy(&otidbuffer, &pkmn[OTIDPOS], OTIDLENGTH);

    return otidbuffer;
}

u16 getSOTID(u8* pkmn) {
    u16 sotidbuffer;
    memcpy(&sotidbuffer, &pkmn[SOTIDPOS], SOTIDLENGTH);

    return sotidbuffer;
}

u32 getPID(u8* pkmn) {
    u32 pidbuffer;
    memcpy(&pidbuffer, &pkmn[PIDPOS], PIDLENGTH);

    return pidbuffer;
}

u16 getTSV(u8* pkmn) {
	u16 TID = getOTID(pkmn);
	u16 SID = getSOTID(pkmn);
	return (TID ^ SID) >> 4;
}

u16 getPokedexNumber(u8* pkmn) {
    u16 pokedexnumber;
    memcpy(&pokedexnumber, &pkmn[POKEDEXNUMBERPOS], POKEDEXNUMBERLENGTH);
    return pokedexnumber;
}

u8 getFriendship(u8* pkmn) {
    u8 friendship;
    memcpy(&friendship, &pkmn[0xA2], 1);
    return friendship;
}

u8 getNature(u8* pkmn) {
    u8 nature;
    memcpy(&nature, &pkmn[NATUREPOS], NATURELENGTH);
    return nature;
}

u8 getEV(u8* pkmn, const int stat) {
    u8 evbuffer[6];
    memcpy(evbuffer, &pkmn[EVPOS], EVLENGTH * 6);

    return evbuffer[stat];
}

u8 getIV(u8* pkmn, const int stat) {
    u32 buffer;
    u8 toreturn;

    memcpy(&buffer, &pkmn[IVPOS], IVLENGTH);
    buffer = buffer >> 5*stat;
    buffer = buffer & 0x1F;
    memcpy(&toreturn, &buffer, 1);

    return toreturn;
}

bool getPokerus(u8* pkmn) {
	u8 pkrs;
	memcpy(&pkrs, &pkmn[0x2B], 1);

	return pkrs;
}

/* ************************ set ************************ */

void setItemEditor(u8* pkmn, u16 item) {
    memcpy(&pkmn[ITEMPOS], &item, ITEMLENGTH);
}

void setAbility(u8* pkmn, const u8 ability) {
    u16 tempspecies = getPokedexNumber(pkmn);
    if (getForm(pkmn))
		memcpy(&tempspecies, &personal.pkmData[getPokedexNumber(pkmn)][0x1C], 2);
	
	u8 abilitynum = 0;
	if (ability == 0)      abilitynum = 1;
	else if (ability == 1) abilitynum = 2;
	else                   abilitynum = 4;
	
	memcpy(&pkmn[ABILITYNUMPOS], &abilitynum, ABILITYNUMLENGTH);
	memcpy(&pkmn[ABILITYPOS], &personal.pkmData[tempspecies][0x18 + ability], ABILITYLENGTH);
}

void setMove(u8* pkmn, const u16 move, const int nmove) {
    memcpy(&pkmn[MOVEPOS + (MOVELENGTH * nmove)], &move, MOVELENGTH);
}

void setEggMove(u8* pkmn, const u16 move, const int nmove) {
    memcpy(&pkmn[EGGMOVEPOS + (EGGMOVELENGTH * nmove)], &move, EGGMOVELENGTH);
}

void setNickname(u8* pkmn, char* nick) {
    u8 toinsert[NICKNAMELENGTH];
    for (int i = 0; i < NICKNAMELENGTH; i++)
        toinsert[i] = 0;

    for (u16 i = 0, nicklen = strlen(nick); i < nicklen; i++)
        toinsert[i * 2] = *(nick + i);

    memcpy(&pkmn[NICKNAMEPOS], toinsert, NICKNAMELENGTH);
}

void setNature(u8* pkmn, const u8 nature) {
    memcpy(&pkmn[NATUREPOS], &nature, NATURELENGTH);
}

void setFriendship(u8* pkmn, const int val) {
	memcpy(&pkmn[0xA2], &val, 1);
	memcpy(&pkmn[0xCA], &val, 1);
}

void setEV(u8* pkmn, u8 val, const int stat) {
    memcpy(&pkmn[EVPOS+(EVLENGTH*stat)], &val, EVLENGTH);
}

void setIV(u8* pkmn, u8 val, const int stat) {
	u32 nval = val;
	u32 mask = 0xFFFFFFFF;
	mask ^= 0x1F << (5 * stat);

	u32 buffer;
	memcpy(&buffer, &pkmn[IVPOS], IVLENGTH);

	buffer &= mask;
	buffer ^= ((nval & 0x1F) << (5 * stat));
	memcpy(&pkmn[IVPOS], &buffer, IVLENGTH);
}

void setHPType(u8* pkmn, const int val) {
    u8 ivstat[6];
    for(int i = 0; i < 6; i++)
        ivstat[i] = getIV(pkmn, i);

    u8 hpivs[16][6] = {
        { 1, 1, 0, 0, 0, 0 }, // Fighting
        { 0, 0, 0, 1, 0, 0 }, // Flying
        { 1, 1, 0, 1, 0, 0 }, // Poison
        { 1, 1, 1, 1, 0, 0 }, // Ground
        { 1, 1, 0, 0, 1, 0 }, // Rock
        { 1, 0, 0, 1, 1, 0 }, // Bug
        { 1, 0, 1, 1, 1, 0 }, // Ghost
        { 1, 1, 1, 1, 1, 0 }, // Steel
        { 1, 0, 1, 0, 0, 1 }, // Fire
        { 1, 0, 0, 1, 0, 1 }, // Water
        { 1, 0, 1, 1, 0, 1 }, // Grass
        { 1, 1, 1, 1, 0, 1 }, // Electric
        { 1, 0, 1, 0, 1, 1 }, // Psychic
        { 1, 0, 0, 1, 1, 1 }, // Ice
        { 1, 0, 1, 1, 1, 1 }, // Dragon
        { 1, 1, 1, 1, 1, 1 }, // Dark
    };

    for(int i = 0; i < 6; i++)
         ivstat[i] = (ivstat[i] & 0x1E) + hpivs[val][i];

    for(int i = 0; i < 6; i++)
        setIV(pkmn, ivstat[i], i);
}

void setShiny(u8* pkmn, const bool shiny) {
	while(isShiny(pkmn) != shiny)
		rerollPID(pkmn);
}

void setLevel(u8* pkmn, int lv) {
    u32 towrite = expTable[lv - 1][personal.pkmData[getPokedexNumber(pkmn)][0x15]];
    memcpy(&pkmn[EXPPOINTPOS], &towrite, EXPPOINTLENGTH);
}

void setWC(u8* mainbuf, u8* wcbuf, int game, int i, int nInjected[]) {
	if (game == GAME_X || game == GAME_Y) {
		*(mainbuf + XYWC6FLAGPOS + i / 8) |= 0x1 << (i % 8);
		memcpy((void*)(mainbuf + XYWC6POS + nInjected[0] * WC6LENGTH), (const void*)wcbuf, WC6LENGTH);
	}

	if (game == GAME_OR || game == GAME_AS) {
		*(mainbuf + ORASWC6FLAGPOS + i / 8) |= 0x1 << (i % 8);
		memcpy((void*)(mainbuf + ORASWC6POS + nInjected[0] * WC6LENGTH), (const void*)wcbuf, WC6LENGTH);

		if (i == 2048) {
			*(mainbuf + EONFLAGPOS)     = 0xC2;
			*(mainbuf + EONFLAGPOS + 1) = 0x73;
			*(mainbuf + EONFLAGPOS + 2) = 0x5D;
			*(mainbuf + EONFLAGPOS + 3) = 0x22;
		}
	}

	if (game == GAME_SUN || game == GAME_MOON) {
		*(mainbuf + SMWC7FLAGPOS + i / 8) |= 0x1 << (i % 8);
		memcpy((void*)(mainbuf + SMWC7POS + nInjected[0] * WC6LENGTH), (const void*)wcbuf, WC6LENGTH);
	}

	if (game == GAME_B1 || game == GAME_W1 || game == GAME_B2 || game == GAME_W2) {
		u32 seed;
		memcpy(&seed, &mainbuf[BWSEEDPOS], sizeof(u32));

		//decrypt
		u16 temp;
		for (int i = 0; i < 0xA90; i += 2) {
			memcpy(&temp, &mainbuf[PGFSTARTPOS + i], 2);
			temp ^= (LCRNG(seed) >> 16);
			seed = LCRNG(seed);
			memcpy(&mainbuf[PGFSTARTPOS + i], &temp, 2);
		}

		*(mainbuf + PGFSTARTPOS + i / 8) |= 0x1 << (i & 7);
		memcpy((void*)(mainbuf + 0x1C900 + nInjected[0] * PGFLENGTH), (const void*)wcbuf, PGFLENGTH);

		//encrypt
		memcpy(&seed, &mainbuf[BWSEEDPOS], sizeof(u32));
		for (int i = 0; i < 0xA90; i += 2) {
			memcpy(&temp, &mainbuf[PGFSTARTPOS + i], 2);
			temp ^= (LCRNG(seed) >> 16);
			seed = LCRNG(seed);
			memcpy(&mainbuf[PGFSTARTPOS + i], &temp, 2);
		}
	}

	nInjected[0] += 1;
	if (game < 4) {
		if (nInjected[0] >= 24)
			nInjected[0] = 0;
	} else if (nInjected[0] >= 48)
		nInjected[0] = 0;
}

void setWC4(u8* mainbuf, u8* wcbuf, int game, int i, int nInjected[], int GBO) {
	if (game == GAME_HG || game == GAME_SS) {
		*(mainbuf + HGSSPGTFLAGPOS + GBO + (i >> 3)) |= 0x1 << (i & 7);
		memcpy((void*)(mainbuf + HGSSPGTPOS + GBO + nInjected[0] * PGTLENGTH), (const void*)wcbuf, PGTLENGTH);
	}
	if (game == GAME_PLATINUM) {
		*(mainbuf + PTPGTFLAGPOS + GBO + (i >> 3)) |= 0x1 << (i & 7);
		memcpy((void*)(mainbuf + PTPGTPOS + GBO + nInjected[0] * PGTLENGTH), (const void*)wcbuf, PGTLENGTH);
	}
	if (game == GAME_DIAMOND || game == GAME_PEARL) {
		*(mainbuf + DPPGTFLAGPOS + GBO + (i >> 3)) |= 0x1 << (i & 7);
		memcpy((void*)(mainbuf + DPPGTPOS + GBO + nInjected[0] * PGTLENGTH), (const void*)wcbuf, PGTLENGTH);
	}

	nInjected[0] += 1;
	if (nInjected[0] >= 8)
		nInjected[0] = 0;
}

void setLanguage(u8* mainbuf, int game, int i) {
	u32 langValues[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x07, 0x08, 0x09, 0x0A};

	if (game < 4)
		*(mainbuf + LANGUAGEPOS) = langValues[i];
	else
		*(mainbuf + 0x1235) = langValues[i];
}

void setMoney(u8* mainbuf, int game, u64 i) {
	if (game < 4) {
		switch (i) {
			case 9999999 : {
				*(mainbuf + MONEYPOS)     = 0x7F;
				*(mainbuf + MONEYPOS + 1) = 0x96;
				*(mainbuf + MONEYPOS + 2) = 0x98;
				break;
			}
		}
	}
	else {
		switch (i) {
			case 9999999 : {
				*(mainbuf + 0x4004)     = 0x7F;
				*(mainbuf + 0x4004 + 1) = 0x96;
				*(mainbuf + 0x4004 + 2) = 0x98;
				break;
			}
		}		
	}
}

void setItem(u8* mainbuf, int type, int game) {
	if (game == GAME_OR || game == GAME_AS) {
		char* paths[] = {"romfs:/misc/oras/base.bin", "romfs:/misc/oras/heals.bin", "romfs:/misc/oras/berries.bin"};
		u32 offset[] = { 0x400, 0xD72, 0xE70 };
		injectFromFile(mainbuf, paths[type], offset[type]);
	} else if (game == GAME_X || game == GAME_Y) {
		char* paths[] = {"romfs:/misc/xy/base.bin", "romfs:/misc/xy/heals.bin", "romfs:/misc/xy/berries.bin"};
		u32 offset[] = { 0x400, 0xD6A, 0xE68 };
		injectFromFile(mainbuf, paths[type], offset[type]);
	} else if (game == GAME_SUN || game == GAME_MOON) {

	}
}

void setBP(u8* mainbuf, int i, int game) {
	const u32 offset[] = {0x423C, 0x423D, 0x4230, 0x4231, 0x411C, 0x411D}; // add offset for SM
	int type = 0;

	if (game == GAME_OR || game == GAME_AS)
		type = 2;
	else if (game == GAME_SUN || game == GAME_MOON) {
		type = 4;
		
		*(mainbuf + 0x50D0C) = 0x7F;
		*(mainbuf + 0x50D0C + 1) = 0x96;
		*(mainbuf + 0x50D0C + 2) = 0x98;
		
		*(mainbuf + 0x50D10) = 0x7F;
		*(mainbuf + 0x50D10 + 1) = 0x96;
		*(mainbuf + 0x50D10 + 2) = 0x98;
	}

	switch (i) {
		case 0 : {
			*(mainbuf + offset[type])     = 0x00;
			*(mainbuf + offset[type + 1]) = 0x00;
			break;
		}
		case 9999 : {
			*(mainbuf + offset[type])     = 0x0F;
			*(mainbuf + offset[type + 1]) = 0x27;
			break;
		}
	}
}

void setPokerus(u8* pkmn) {
	*(pkmn + 0x2B) = POKERUS;
}

void setBadges(u8* mainbuf, int game, int i) {
	const u32 value[9] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

	if (game < 4)
		*(mainbuf + BADGEPOS) = value[i];
}

void setTM(u8* mainbuf, int game) {
	if (game == GAME_OR || game == GAME_AS)
		injectFromFile(mainbuf, "romfs:/misc/oras/tm.bin", 0xBC0);
	else if (game == GAME_X || game == GAME_Y)
		injectFromFile(mainbuf, "romfs:/misc/xy/tm.bin", 0xBC0);
	else if (game == GAME_SUN || game == GAME_MOON)
		injectFromFile(mainbuf, "romfs:/misc/sm/tm.bin", 0x0);
}

void saveFileEditor(u8* mainbuf, int game) {
	int currentEntry = 0;
	int langCont = 0;
	int badgeCont = 0;

	while(aptMainLoop()) {
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);		
		if ((hidKeysDown() & KEY_TOUCH) && touch.px > 301 && touch.px < 320 && touch.py > 205 && touch.py < 223) break;

		if (hidKeysDown() & KEY_B)
			break;

		if (hidKeysDown() & KEY_DUP) {
			if (currentEntry > 0) currentEntry--;
			else if (currentEntry == 0) currentEntry = 9;
		}

		if (hidKeysDown() & KEY_DDOWN) {
			if (currentEntry < 9) currentEntry++;
			else if (currentEntry == 9) currentEntry = 0;
		}

		if (hidKeysDown() & KEY_DLEFT) {
			if (currentEntry >= 5) currentEntry -= 5;
		}

		if (hidKeysDown() & KEY_DRIGHT) {
			if (currentEntry <= 4) currentEntry += 5;
		}

		if (hidKeysDown() & KEY_A) {
			switch (currentEntry) {
				case 0 : {
					int langMax = (game < 4) ? 6 : 8;
					if (langCont < langMax) langCont++;
					else if (langCont == langMax) langCont = 0;
					break;
				}
				case 6 : {
					if (badgeCont < 8) badgeCont++;
					else if (badgeCont == 8) badgeCont = 0;
					break;
				}
			}
		}

		if (hidKeysDown() & KEY_START) {
			switch (currentEntry) {
				case 0 : {
					setLanguage(mainbuf, game, langCont);
					infoDisp("Language set successfully!");
					break;
				}
				case 1 : {
					setBP(mainbuf, 9999, game);
					infoDisp("Battle Points set successfully!");
					break;
				}
				case 2 : {
				//	infoDisp("Balls injected successfully!");
					break;
				}
				case 3 : {
					if (game < 4) {
						setItem(mainbuf, 1, game);
						infoDisp("Heals injected successfully!");
					} else
						infoDisp("Not currently available for SM");
					break;
				}
				case 4 : {
					if (game < 4) {
						setItem(mainbuf, 0, game);
						infoDisp("Items injected successfully!");
					} else
						infoDisp("Not currently available for SM");
					break;
				}
				case 5 : {
					setMoney(mainbuf, game, 9999999);
					infoDisp("Money set successfully!");
					break;
				}
				case 6 : {
					if (game < 4) {
						setBadges(mainbuf, game, badgeCont);
						infoDisp("Badges set successfully!");
					} else
						infoDisp("Not currently available for SM");
					break;
				}
				case 7 : {
					if (game < 4) {
						setTM(mainbuf, game);
						infoDisp("TMs set successfully!");
					} else
						infoDisp("Not currently available for SM");
					break;
				}
				case 8 : {
					int start = 0;
					int wcmax = (game < 4) ? 24 : 48;
					if (game == GAME_X || game == GAME_Y)
						start = XYWC6FLAGPOS;
					else if (game == GAME_OR || game == GAME_AS)
						start = ORASWC6FLAGPOS;
					else if (game == GAME_SUN || game == GAME_MOON)
						start = SMWC7FLAGPOS;

					for (int i = 0; i < (0x100 + wcmax * WC6LENGTH); i++)
						*(mainbuf + start + i) = 0x00;
					infoDisp("Mistery Gift box cleaned!");
					break;
				}
				case 9 : {
					if (game < 4) {
						setItem(mainbuf, 2, game);
						infoDisp("Berries set successfully!");
					} else
						infoDisp("Not currently available for SM");
					break;
				}
			}
		}

		printEditor(currentEntry, langCont, badgeCont);
	}
}

void itemEditor(u8* pkmn, int game) {
	int itemsSorted[] = {0};
	int currentEntry = 0;
	int page = 0, maxpages = 23;
	
	while (aptMainLoop()) {
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);
		
		if (hidKeysDown() & KEY_B) break;
		
		if (hidKeysDown() & KEY_L) {
			if (page > 0) page--;
			else if (page == 0) page = maxpages - 1;
		}
		
		if (hidKeysDown() & KEY_R) {
			if (page < maxpages - 1) page++;
			else if (page == maxpages - 1) page = 0;
		}
		
		if (hidKeysDown() & KEY_DUP) {
			if (currentEntry > 0) currentEntry--;
			else if (currentEntry == 0) currentEntry = 39;
		}
		
		if (hidKeysDown() & KEY_DDOWN) {
			if (currentEntry < 39) currentEntry++;
			else if (currentEntry == 39) currentEntry = 0;
		}
		
		if (hidKeysDown() & KEY_DLEFT) {
			if (currentEntry <= 19)	{
				page--;
				if (page < 0) 
					page = maxpages - 1;
			}
			else if (currentEntry >= 20) currentEntry -= 20;
		}
		
		if (hidKeysDown() & KEY_DRIGHT) {
			if (currentEntry <= 19) currentEntry += 20;
			else if (currentEntry >= 20) {
				page++;
				if (page > maxpages - 1)
					page = 0;
			}
		}
		
		if (hidKeysDown() & KEY_A)
			setItemEditor(pkmn, itemsSorted[currentEntry + page * 40]);
		
		printItems(pkmn, currentEntry, page);
	}
}

void movesEditor(u8* pkmn, int game) {
	int movesSorted[] = {0};
	int currentEntry = 0;
	int entryBottom = 0;
	int page = 0, maxpages = 18;
	
	while (aptMainLoop()) {
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);
		
		if (hidKeysDown() & KEY_B) break;
		
		if (hidKeysDown() & KEY_L) {
			if (page > 0) page--;
			else if (page == 0) page = maxpages - 1;
		}
		
		if (hidKeysDown() & KEY_R) {
			if (page < maxpages - 1) page++;
			else if (page == maxpages - 1) page = 0;
		}
		
		if (hidKeysDown() & KEY_DUP) {
			if (currentEntry > 0) currentEntry--;
			else if (currentEntry == 0) currentEntry = 39;
		}
		
		if (hidKeysDown() & KEY_DDOWN) {
			if (currentEntry < 39) currentEntry++;
			else if (currentEntry == 39) currentEntry = 0;
		}
		
		if (hidKeysDown() & KEY_DLEFT) {
			if (currentEntry <= 19)	{
				page--;
				if (page < 0) 
					page = maxpages - 1;
			}
			else if (currentEntry >= 20) currentEntry -= 20;
		}
		
		if (hidKeysDown() & KEY_DRIGHT) {
			if (currentEntry <= 19) currentEntry += 20;
			else if (currentEntry >= 20) {
				page++;
				if (page > maxpages - 1)
					page = 0;
			}
		}
		
		if (hidKeysDown() & KEY_TOUCH) {
			if (touch.px > 123 && touch.px < 301 && touch.py > 10 && touch.py < 36)   entryBottom = 0;
			if (touch.px > 123 && touch.px < 301 && touch.py > 36 && touch.py < 62)   entryBottom = 1;
			if (touch.px > 123 && touch.px < 301 && touch.py > 62 && touch.py < 88)   entryBottom = 2;
			if (touch.px > 123 && touch.px < 301 && touch.py > 88 && touch.py < 114)  entryBottom = 3;
			if (touch.px > 123 && touch.px < 301 && touch.py > 129 && touch.py < 155) entryBottom = 4;
			if (touch.px > 123 && touch.px < 301 && touch.py > 155 && touch.py < 181) entryBottom = 5;
			if (touch.px > 123 && touch.px < 301 && touch.py > 181 && touch.py < 207) entryBottom = 6;
			if (touch.px > 123 && touch.px < 301 && touch.py > 207 && touch.py < 233) entryBottom = 7;
		}
		
		if (hidKeysDown() & KEY_A) {
			if (entryBottom < 4)
				setMove(pkmn, movesSorted[currentEntry + page * 40], entryBottom);
			else
				setEggMove(pkmn, movesSorted[currentEntry + page * 40], entryBottom - 4);
		}
		
		printMoves(pkmn, currentEntry, entryBottom, page);
	}
}

void pokemonEditor(u8* mainbuf, int game) {
	bool speedy = false;
	bool cloning = false;
	int box = 0;
	int currentEntry = 0;
	int boxmax = (game < 4) ? 30 : 31;
	int ability = 2;

	while (aptMainLoop()) {
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);

		if (hidKeysDown() & KEY_B) break;

		if (hidKeysDown() & KEY_R) {
			if (box < boxmax) box++;
			else if (box == boxmax) box = 0;
		}

		if (hidKeysDown() & KEY_L) {
			if (box > 0) box--;
			else if (box == 0) box = boxmax;
		}

		if (hidKeysDown() & KEY_TOUCH) {
			if (touch.px > 2 && touch.px < 17 && touch.py > 11 && touch.py < 33) {
				if (box > 0) box--;
				else if (box == 0) box = boxmax;
			}
			if (touch.px > 185 && touch.px < 200 && touch.py > 11 && touch.py < 33) {
				if (box < boxmax) box++;
				else if (box == boxmax) box = 0;
			}
			if (touch.px > 288 && touch.px < 310 && touch.py > 217 && touch.py < 235) break;
		}

		if (hidKeysDown() & KEY_DRIGHT) {
			if (currentEntry < 29) currentEntry++;
			else if (currentEntry == 29) currentEntry = 0;
		}

		if (hidKeysDown() & KEY_DLEFT) {
			if (currentEntry > 0) currentEntry--;
			else if (currentEntry == 0) currentEntry = 29;
		}

		if (hidKeysDown() & KEY_DUP) {
			if (currentEntry >= 6) currentEntry -= 6;
		}

		if (hidKeysDown() & KEY_DDOWN) {
			if (currentEntry <= 23) currentEntry += 6;
		}

		if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH && touch.px > 214 && touch.px < 320 && touch.py > 89 && touch.py < 120)) {
			u8* pkmn = (u8*)malloc(PKMNLENGTH * sizeof(u8));
			getPkmn(mainbuf, box, currentEntry, pkmn, game);

			while (aptMainLoop() && getPokedexNumber(pkmn)) {
				hidScanInput();
				hidTouchRead(&touch);

				if (hidKeysDown() & KEY_B) break;

				if (hidKeysDown() & KEY_L)
					speedy = false;

				if (hidKeysDown() & KEY_R)
					speedy = true;

				if (hidKeysDown() & KEY_TOUCH) {
					if (touch.px > 288 && touch.px < 310 && touch.py > 213 && touch.py < 231) break;
					
					if (touch.px > 126 && touch.px < 141 && touch.py > 60 && touch.py < 72) {
						if (getNature(pkmn) < 24)
							setNature(pkmn, getNature(pkmn) + 1);
						else if (getNature(pkmn) == 24)
							setNature(pkmn, 0);
					}
					
					if (touch.px > 150 && touch.px < 165 && touch.py > 144 && touch.py < 156) {
						if (ability < 2) ability++;
						else if (ability == 2) ability = 0;
						setAbility(pkmn, ability);
					}
					
					if (touch.px > 126 && touch.px < 141 && touch.py > 94 && touch.py < 106) {
						itemEditor(pkmn, game);
					}

					if (touch.px > 126 && touch.px < 141 && touch.py > 111 && touch.py < 123) {
						if (isShiny(pkmn))
							setShiny(pkmn, false);
						else setShiny(pkmn, true);
					}

					if (touch.px > 126 && touch.px < 141 && touch.py > 128 && touch.py < 140) {
						if (!(getPokerus(pkmn)))
							setPokerus(pkmn);
						else *(pkmn + 0x2B) = 0x00;
					}

					if (touch.px > 162 && touch.px < 177 && touch.py > 162 && touch.py < 174) {
						static SwkbdState swkbd;
						static char buf[60];

						SwkbdButton button = SWKBD_BUTTON_NONE;
						swkbdInit(&swkbd, SWKBD_TYPE_NORMAL, 2, (NICKNAMELENGTH / 2) - 1);
						swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Cancel", false);
						swkbdSetButton(&swkbd, SWKBD_BUTTON_RIGHT, "Set", true);
						swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK, SWKBD_FILTER_DIGITS | SWKBD_FILTER_AT | SWKBD_FILTER_PERCENT | SWKBD_FILTER_BACKSLASH | SWKBD_FILTER_PROFANITY, 2);
						swkbdSetFeatures(&swkbd, SWKBD_MULTILINE);
						swkbdSetHintText(&swkbd, "Enter your nickname");
						button = swkbdInputText(&swkbd, buf, sizeof(buf));

						static char nick[NICKNAMELENGTH];
						for (int i = 0; i < NICKNAMELENGTH; i++)
							nick[i] = 0;
						memcpy(nick, buf, NICKNAMELENGTH);
						nick[NICKNAMELENGTH - 1] = '\0';

						if (button != SWKBD_BUTTON_NONE)
							setNickname(pkmn, nick);
					}

					if (touch.px > 162 && touch.px < 177 && touch.py > 178 && touch.py < 190) {
						if (getHPType(pkmn) < 15)
							setHPType(pkmn, getHPType(pkmn) + 1);
						else if (getHPType(pkmn) == 15)
							setHPType(pkmn, 0);
					}

					if (touch.px > 200 && touch.px < 308 && touch.py > 170 && touch.py < 200) {
						setPkmn(mainbuf, box, currentEntry, pkmn, game);
						infoDisp("Edits applied!");
						break;
					}

					if (touch.px > 200 && touch.px < 308 && touch.py > 140 && touch.py < 170) {
						movesEditor(pkmn, game);
					}
				}

				if ((hidKeysDown() & KEY_TOUCH) && !(speedy)) {
					if (touch.px > 127 && touch.px < 140 && touch.py > 42 && touch.py < 55) {
						if (getLevel(pkmn) < 100)
							setLevel(pkmn, getLevel(pkmn) + 1);
						else if (getLevel(pkmn) == 100)
							setLevel(pkmn, 1);
					}
					
					if (touch.px > 86 && touch.px < 99 && touch.py > 42 && touch.py < 55) {
						if (getLevel(pkmn) > 1)
							setLevel(pkmn, getLevel(pkmn) - 1);
						else if (getLevel(pkmn) == 1)
							setLevel(pkmn, 100);
					}
					
					if (touch.px > 86 && touch.px < 99 && touch.py > 76 && touch.py < 89) {
						if (getFriendship(pkmn) > 0)
							setFriendship(pkmn, getFriendship(pkmn) - 1);
					}

					if (touch.px > 127 && touch.px < 140 && touch.py > 76 && touch.py < 89) {
						if (getFriendship(pkmn) < 255)
							setFriendship(pkmn, getFriendship(pkmn) + 1);
					}

					// - ivs
					if (touch.px > 207 && touch.px < 220 && touch.py > 27 && touch.py < 40)
						if (getIV(pkmn, 0) > 0)
							setIV(pkmn, getIV(pkmn, 0) - 1, 0);

					if (touch.px > 207 && touch.px < 220 && touch.py > 44 && touch.py < 57)
						if (getIV(pkmn, 1) > 0)
							setIV(pkmn, getIV(pkmn, 1) - 1, 1);

					if (touch.px > 207 && touch.px < 220 && touch.py > 61 && touch.py < 74)
						if (getIV(pkmn, 2) > 0)
							setIV(pkmn, getIV(pkmn, 2) - 1, 2);

					if (touch.px > 207 && touch.px < 220 && touch.py > 78 && touch.py < 91)
						if (getIV(pkmn, 4) > 0)
							setIV(pkmn, getIV(pkmn, 4) - 1, 4);

					if (touch.px > 207 && touch.px < 220 && touch.py > 95 && touch.py < 108)
						if (getIV(pkmn, 5) > 0)
							setIV(pkmn, getIV(pkmn, 5) - 1, 5);

					if (touch.px > 207 && touch.px < 220 && touch.py > 112 && touch.py < 125)
						if (getIV(pkmn, 3) > 0)
							setIV(pkmn, getIV(pkmn, 3) - 1, 3);

					// + ivs
					if (touch.px > 242 && touch.px < 255 && touch.py > 27 && touch.py < 40)
						if (getIV(pkmn, 0) < 31)
							setIV(pkmn, getIV(pkmn, 0) + 1, 0);

					if (touch.px > 242 && touch.px < 255 && touch.py > 44 && touch.py < 57)
						if (getIV(pkmn, 1) < 31)
							setIV(pkmn, getIV(pkmn, 1) + 1, 1);

					if (touch.px > 242 && touch.px < 255 && touch.py > 61 && touch.py < 74)
						if (getIV(pkmn, 2) < 31)
							setIV(pkmn, getIV(pkmn, 2) + 1, 2);

					if (touch.px > 242 && touch.px < 255 && touch.py > 78 && touch.py < 91)
						if (getIV(pkmn, 4) < 31)
							setIV(pkmn, getIV(pkmn, 4) + 1, 4);

					if (touch.px > 242 && touch.px < 255 && touch.py > 95 && touch.py < 108)
						if (getIV(pkmn, 5) < 31)
							setIV(pkmn, getIV(pkmn, 5) + 1, 5);

					if (touch.px > 242 && touch.px < 255 && touch.py > 112 && touch.py < 125)
						if (getIV(pkmn, 3) < 31)
							setIV(pkmn, getIV(pkmn, 3) + 1, 3);

					// - evs
					if (touch.px > 257 && touch.px < 270 && touch.py > 27 && touch.py < 40)
						if (getEV(pkmn, 0) > 0)
							setEV(pkmn, getEV(pkmn, 0) - 1, 0);

					if (touch.px > 257 && touch.px < 270 && touch.py > 44 && touch.py < 57)
						if (getEV(pkmn, 1) > 0)
							setEV(pkmn, getEV(pkmn, 1) - 1, 1);

					if (touch.px > 257 && touch.px < 270 && touch.py > 61 && touch.py < 74)
						if (getEV(pkmn, 2) > 0)
							setEV(pkmn, getEV(pkmn, 2) - 1, 2);

					if (touch.px > 257 && touch.px < 270 && touch.py > 78 && touch.py < 91)
						if (getEV(pkmn, 4) > 0)
							setEV(pkmn, getEV(pkmn, 4) - 1, 4);

					if (touch.px > 257 && touch.px < 270 && touch.py > 95 && touch.py < 108)
						if (getEV(pkmn, 5) > 0)
							setEV(pkmn, getEV(pkmn, 5) - 1, 5);

					if (touch.px > 257 && touch.px < 270 && touch.py > 112 && touch.py < 125)
						if (getEV(pkmn, 3) > 0)
							setEV(pkmn, getEV(pkmn, 3) - 1, 3);

					// + evs
					if ((getEV(pkmn, 0) + getEV(pkmn, 1) + getEV(pkmn, 2) + getEV(pkmn, 3) + getEV(pkmn, 4) + getEV(pkmn, 5)) < 510) {
						if (touch.px > 296 && touch.px < 309 && touch.py > 27 && touch.py < 40)
							if (getEV(pkmn, 0) < 252)
								setEV(pkmn, getEV(pkmn, 0) + 1, 0);

						if (touch.px > 296 && touch.px < 309 && touch.py > 44 && touch.py < 57)
							if (getEV(pkmn, 1) < 252)
								setEV(pkmn, getEV(pkmn, 1) + 1, 1);

						if (touch.px > 296 && touch.px < 309 && touch.py > 61 && touch.py < 74)
							if (getEV(pkmn, 2) < 252)
								setEV(pkmn, getEV(pkmn, 2) + 1, 2);

						if (touch.px > 296 && touch.px < 309 && touch.py > 78 && touch.py < 91)
							if (getEV(pkmn, 4) < 252)
								setEV(pkmn, getEV(pkmn, 4) + 1, 4);

						if (touch.px > 296 && touch.px < 309 && touch.py > 95 && touch.py < 108)
							if (getEV(pkmn, 5) < 252)
								setEV(pkmn, getEV(pkmn, 5) + 1, 5);

						if (touch.px > 296 && touch.px < 309 && touch.py > 112 && touch.py < 125)
							if (getEV(pkmn, 3) < 252)
								setEV(pkmn, getEV(pkmn, 3) + 1, 3);
					}
				}

				if ((hidKeysHeld() & KEY_TOUCH) && speedy) {
					if (touch.px > 127 && touch.px < 140 && touch.py > 42 && touch.py < 55) {
						if (getLevel(pkmn) < 100)
							setLevel(pkmn, getLevel(pkmn) + 1);
						else if (getLevel(pkmn) == 100)
							setLevel(pkmn, 1);
					}
					
					if (touch.px > 86 && touch.px < 99 && touch.py > 42 && touch.py < 55) {
						if (getLevel(pkmn) > 1)
							setLevel(pkmn, getLevel(pkmn) - 1);
						else if (getLevel(pkmn) == 1)
							setLevel(pkmn, 100);
					}
					
					if (touch.px > 86 && touch.px < 99 && touch.py > 76 && touch.py < 89) {
						if (getFriendship(pkmn) > 0)
							setFriendship(pkmn, getFriendship(pkmn) - 1);
					}

					if (touch.px > 127 && touch.px < 140 && touch.py > 76 && touch.py < 89) {
						if (getFriendship(pkmn) < 255)
							setFriendship(pkmn, getFriendship(pkmn) + 1);
					}

					// - ivs
					if (touch.px > 207 && touch.px < 220 && touch.py > 27 && touch.py < 40)
						if (getIV(pkmn, 0) > 0)
							setIV(pkmn, getIV(pkmn, 0) - 1, 0);

					if (touch.px > 207 && touch.px < 220 && touch.py > 44 && touch.py < 57)
						if (getIV(pkmn, 1) > 0)
							setIV(pkmn, getIV(pkmn, 1) - 1, 1);

					if (touch.px > 207 && touch.px < 220 && touch.py > 61 && touch.py < 74)
						if (getIV(pkmn, 2) > 0)
							setIV(pkmn, getIV(pkmn, 2) - 1, 2);

					if (touch.px > 207 && touch.px < 220 && touch.py > 78 && touch.py < 91)
						if (getIV(pkmn, 4) > 0)
							setIV(pkmn, getIV(pkmn, 4) - 1, 4);

					if (touch.px > 207 && touch.px < 220 && touch.py > 95 && touch.py < 108)
						if (getIV(pkmn, 5) > 0)
							setIV(pkmn, getIV(pkmn, 5) - 1, 5);

					if (touch.px > 207 && touch.px < 220 && touch.py > 112 && touch.py < 125)
						if (getIV(pkmn, 3) > 0)
							setIV(pkmn, getIV(pkmn, 3) - 1, 3);

					// + ivs
					if (touch.px > 242 && touch.px < 255 && touch.py > 27 && touch.py < 40)
						if (getIV(pkmn, 0) < 31)
							setIV(pkmn, getIV(pkmn, 0) + 1, 0);

					if (touch.px > 242 && touch.px < 255 && touch.py > 44 && touch.py < 57)
						if (getIV(pkmn, 1) < 31)
							setIV(pkmn, getIV(pkmn, 1) + 1, 1);

					if (touch.px > 242 && touch.px < 255 && touch.py > 61 && touch.py < 74)
						if (getIV(pkmn, 2) < 31)
							setIV(pkmn, getIV(pkmn, 2) + 1, 2);

					if (touch.px > 242 && touch.px < 255 && touch.py > 78 && touch.py < 91)
						if (getIV(pkmn, 4) < 31)
							setIV(pkmn, getIV(pkmn, 4) + 1, 4);

					if (touch.px > 242 && touch.px < 255 && touch.py > 95 && touch.py < 108)
						if (getIV(pkmn, 5) < 31)
							setIV(pkmn, getIV(pkmn, 5) + 1, 5);

					if (touch.px > 242 && touch.px < 255 && touch.py > 112 && touch.py < 125)
						if (getIV(pkmn, 3) < 31)
							setIV(pkmn, getIV(pkmn, 3) + 1, 3);

					// - evs
					if (touch.px > 257 && touch.px < 270 && touch.py > 27 && touch.py < 40)
						if (getEV(pkmn, 0) > 0)
							setEV(pkmn, getEV(pkmn, 0) - 1, 0);

					if (touch.px > 257 && touch.px < 270 && touch.py > 44 && touch.py < 57)
						if (getEV(pkmn, 1) > 0)
							setEV(pkmn, getEV(pkmn, 1) - 1, 1);

					if (touch.px > 257 && touch.px < 270 && touch.py > 61 && touch.py < 74)
						if (getEV(pkmn, 2) > 0)
							setEV(pkmn, getEV(pkmn, 2) - 1, 2);

					if (touch.px > 257 && touch.px < 270 && touch.py > 78 && touch.py < 91)
						if (getEV(pkmn, 4) > 0)
							setEV(pkmn, getEV(pkmn, 4) - 1, 4);

					if (touch.px > 257 && touch.px < 270 && touch.py > 95 && touch.py < 108)
						if (getEV(pkmn, 5) > 0)
							setEV(pkmn, getEV(pkmn, 5) - 1, 5);

					if (touch.px > 257 && touch.px < 270 && touch.py > 112 && touch.py < 125)
						if (getEV(pkmn, 3) > 0)
							setEV(pkmn, getEV(pkmn, 3) - 1, 3);

					// + evs
					if ((getEV(pkmn, 0) + getEV(pkmn, 1) + getEV(pkmn, 2) + getEV(pkmn, 3) + getEV(pkmn, 4) + getEV(pkmn, 5)) < 510) {
						if (touch.px > 296 && touch.px < 309 && touch.py > 27 && touch.py < 40)
							if (getEV(pkmn, 0) < 252)
								setEV(pkmn, getEV(pkmn, 0) + 1, 0);

						if (touch.px > 296 && touch.px < 309 && touch.py > 44 && touch.py < 57)
							if (getEV(pkmn, 1) < 252)
								setEV(pkmn, getEV(pkmn, 1) + 1, 1);

						if (touch.px > 296 && touch.px < 309 && touch.py > 61 && touch.py < 74)
							if (getEV(pkmn, 2) < 252)
								setEV(pkmn, getEV(pkmn, 2) + 1, 2);

						if (touch.px > 296 && touch.px < 309 && touch.py > 78 && touch.py < 91)
							if (getEV(pkmn, 4) < 252)
								setEV(pkmn, getEV(pkmn, 4) + 1, 4);

						if (touch.px > 296 && touch.px < 309 && touch.py > 95 && touch.py < 108)
							if (getEV(pkmn, 5) < 252)
								setEV(pkmn, getEV(pkmn, 5) + 1, 5);

						if (touch.px > 296 && touch.px < 309 && touch.py > 112 && touch.py < 125)
							if (getEV(pkmn, 3) < 252)
								setEV(pkmn, getEV(pkmn, 3) + 1, 3);
					}
				}

				printPKEditor(pkmn, game, speedy);
			}

			free(pkmn);
		}

		if (hidKeysHeld() & KEY_TOUCH) {
			if (touch.px > 4 && touch.px < 38 && touch.py > 45 && touch.py < 75) currentEntry = 0;
			if (touch.px > 38 && touch.px < 72 && touch.py > 45 && touch.py < 75) currentEntry = 1;
			if (touch.px > 72 && touch.px < 106 && touch.py > 45 && touch.py < 75) currentEntry = 2;
			if (touch.px > 106 && touch.px < 140 && touch.py > 45 && touch.py < 75) currentEntry = 3;
			if (touch.px > 140 && touch.px < 174 && touch.py > 45 && touch.py < 75) currentEntry = 4;
			if (touch.px > 174 && touch.px < 208 && touch.py > 45 && touch.py < 75) currentEntry = 5;
			if (touch.px > 4 && touch.px < 38 && touch.py > 75 && touch.py < 105) currentEntry = 6;
			if (touch.px > 38 && touch.px < 72 && touch.py > 75 && touch.py < 105) currentEntry = 7;
			if (touch.px > 72 && touch.px < 106 && touch.py > 75 && touch.py < 105) currentEntry = 8;
			if (touch.px > 106 && touch.px < 140 && touch.py > 75 && touch.py < 105) currentEntry = 9;
			if (touch.px > 140 && touch.px < 174 && touch.py > 75 && touch.py < 105) currentEntry = 10;
			if (touch.px > 174 && touch.px < 208 && touch.py > 75 && touch.py < 105) currentEntry = 11;
			if (touch.px > 4 && touch.px < 38 && touch.py > 105 && touch.py < 135) currentEntry = 12;
			if (touch.px > 38 && touch.px < 72 && touch.py > 105 && touch.py < 135) currentEntry = 13;
			if (touch.px > 72 && touch.px < 106 && touch.py > 105 && touch.py < 135) currentEntry = 14;
			if (touch.px > 106 && touch.px < 140 && touch.py > 105 && touch.py < 135) currentEntry = 15;
			if (touch.px > 140 && touch.px < 174 && touch.py > 105 && touch.py < 135) currentEntry = 16;
			if (touch.px > 174 && touch.px < 208 && touch.py > 105 && touch.py < 135) currentEntry = 17;
			if (touch.px > 4 && touch.px < 38 && touch.py > 135 && touch.py < 165) currentEntry = 18;
			if (touch.px > 38 && touch.px < 72 && touch.py > 135 && touch.py < 165) currentEntry = 19;
			if (touch.px > 72 && touch.px < 106 && touch.py > 135 && touch.py < 165) currentEntry = 20;
			if (touch.px > 106 && touch.px < 140 && touch.py > 135 && touch.py < 165) currentEntry = 21;
			if (touch.px > 140 && touch.px < 174 && touch.py > 135 && touch.py < 165) currentEntry = 22;
			if (touch.px > 174 && touch.px < 208 && touch.py > 135 && touch.py < 165) currentEntry = 23;
			if (touch.px > 4 && touch.px < 38 && touch.py > 165 && touch.py < 195) currentEntry = 24;
			if (touch.px > 38 && touch.px < 72 && touch.py > 165 && touch.py < 195) currentEntry = 25;
			if (touch.px > 72 && touch.px < 106 && touch.py > 165 && touch.py < 195) currentEntry = 26;
			if (touch.px > 106 && touch.px < 140 && touch.py > 165 && touch.py < 195) currentEntry = 27;
			if (touch.px > 140 && touch.px < 174 && touch.py > 165 && touch.py < 195) currentEntry = 28;
			if (touch.px > 174 && touch.px < 208 && touch.py > 165 && touch.py < 195) currentEntry = 29;
		}

		if ((hidKeysDown() & KEY_Y) || (hidKeysDown() & KEY_TOUCH && touch.px > 214 && touch.px < 320 && touch.py > 121 && touch.py < 151)) {
			u8* pkmn = (u8*)malloc(PKMNLENGTH * sizeof(u8));
			getPkmn(mainbuf, box, currentEntry, pkmn, game);

			cloning = true;
			while(aptMainLoop()) {
				hidScanInput();
				touchPosition touch;
				hidTouchRead(&touch);

				if (hidKeysDown() & KEY_B) break;

				if (hidKeysDown() & KEY_R) {
					if (box < boxmax) box++;
					else if (box == boxmax) box = 0;
				}

				if (hidKeysDown() & KEY_L) {
					if (box > 0) box--;
					else if (box == 0) box = boxmax;
				}

				if (hidKeysDown() & KEY_TOUCH) {
					if (touch.px > 2 && touch.px < 17 && touch.py > 11 && touch.py < 33) {
						if (box > 0) box--;
						else if (box == 0) box = boxmax;
					}
					if (touch.px > 185 && touch.px < 200 && touch.py > 11 && touch.py < 33) {
						if (box < boxmax) box++;
						else if (box == boxmax) box = 0;
					}
				}

				if (hidKeysDown() & KEY_DRIGHT) {
					if (currentEntry < 29) currentEntry++;
					else if (currentEntry == 29) currentEntry = 0;
				}

				if (hidKeysDown() & KEY_DLEFT) {
					if (currentEntry > 0) currentEntry--;
					else if (currentEntry == 0) currentEntry = 29;
				}

				if (hidKeysDown() & KEY_DUP) {
					if (currentEntry >= 6) currentEntry -= 6;
				}

				if (hidKeysDown() & KEY_DDOWN) {
					if (currentEntry <= 23) currentEntry += 6;
				}

				if (hidKeysHeld() & KEY_TOUCH) {
					if (touch.px > 4 && touch.px < 38 && touch.py > 45 && touch.py < 75) currentEntry = 0;
					if (touch.px > 38 && touch.px < 72 && touch.py > 45 && touch.py < 75) currentEntry = 1;
					if (touch.px > 72 && touch.px < 106 && touch.py > 45 && touch.py < 75) currentEntry = 2;
					if (touch.px > 106 && touch.px < 140 && touch.py > 45 && touch.py < 75) currentEntry = 3;
					if (touch.px > 140 && touch.px < 174 && touch.py > 45 && touch.py < 75) currentEntry = 4;
					if (touch.px > 174 && touch.px < 208 && touch.py > 45 && touch.py < 75) currentEntry = 5;
					if (touch.px > 4 && touch.px < 38 && touch.py > 75 && touch.py < 105) currentEntry = 6;
					if (touch.px > 38 && touch.px < 72 && touch.py > 75 && touch.py < 105) currentEntry = 7;
					if (touch.px > 72 && touch.px < 106 && touch.py > 75 && touch.py < 105) currentEntry = 8;
					if (touch.px > 106 && touch.px < 140 && touch.py > 75 && touch.py < 105) currentEntry = 9;
					if (touch.px > 140 && touch.px < 174 && touch.py > 75 && touch.py < 105) currentEntry = 10;
					if (touch.px > 174 && touch.px < 208 && touch.py > 75 && touch.py < 105) currentEntry = 11;
					if (touch.px > 4 && touch.px < 38 && touch.py > 105 && touch.py < 135) currentEntry = 12;
					if (touch.px > 38 && touch.px < 72 && touch.py > 105 && touch.py < 135) currentEntry = 13;
					if (touch.px > 72 && touch.px < 106 && touch.py > 105 && touch.py < 135) currentEntry = 14;
					if (touch.px > 106 && touch.px < 140 && touch.py > 105 && touch.py < 135) currentEntry = 15;
					if (touch.px > 140 && touch.px < 174 && touch.py > 105 && touch.py < 135) currentEntry = 16;
					if (touch.px > 174 && touch.px < 208 && touch.py > 105 && touch.py < 135) currentEntry = 17;
					if (touch.px > 4 && touch.px < 38 && touch.py > 135 && touch.py < 165) currentEntry = 18;
					if (touch.px > 38 && touch.px < 72 && touch.py > 135 && touch.py < 165) currentEntry = 19;
					if (touch.px > 72 && touch.px < 106 && touch.py > 135 && touch.py < 165) currentEntry = 20;
					if (touch.px > 106 && touch.px < 140 && touch.py > 135 && touch.py < 165) currentEntry = 21;
					if (touch.px > 140 && touch.px < 174 && touch.py > 135 && touch.py < 165) currentEntry = 22;
					if (touch.px > 174 && touch.px < 208 && touch.py > 135 && touch.py < 165) currentEntry = 23;
					if (touch.px > 4 && touch.px < 38 && touch.py > 165 && touch.py < 195) currentEntry = 24;
					if (touch.px > 38 && touch.px < 72 && touch.py > 165 && touch.py < 195) currentEntry = 25;
					if (touch.px > 72 && touch.px < 106 && touch.py > 165 && touch.py < 195) currentEntry = 26;
					if (touch.px > 106 && touch.px < 140 && touch.py > 165 && touch.py < 195) currentEntry = 27;
					if (touch.px > 140 && touch.px < 174 && touch.py > 165 && touch.py < 195) currentEntry = 28;
					if (touch.px > 174 && touch.px < 208 && touch.py > 165 && touch.py < 195) currentEntry = 29;
				}

				if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH && touch.px > 214 && touch.px < 320 && touch.py > 121 && touch.py < 151)) {
					setPkmn(mainbuf, box, currentEntry, pkmn, game);
					break;
				}

				printPKViewer(mainbuf, game, currentEntry, box, cloning);
			}

			free(pkmn);
			cloning = false;
		}

		printPKViewer(mainbuf, game, currentEntry, box, cloning);
	}
}
