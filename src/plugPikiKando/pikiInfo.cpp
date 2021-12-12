#include "types.h"

/*
 * --INFO--
 * Address:	80119CE4
 * Size:	000024
 */
class PikiInfo {
    s32 pikiCountA; // _00
    s32 pikiCountB; // _04
    u32 _08;
    u32 _0C;
    u32 _10;
    u32 _14;
    u32 _18;

    PikiInfo();
    void addFormationPiki();
    void subFormationPiki();
};

PikiInfo::PikiInfo()
{
    pikiCountB = 0;
    pikiCountA = 0;
    _08 = 0;
    _18 = 0;
    _14 = 0;
    _10 = 0;
    _0C = 0;
}

/*
 * --INFO--
 * Address:	80119D08
 * Size:	000024
 */
void PikiInfo::addFormationPiki(void) {
    pikiCountA += 1;
    if (pikiCountB >= pikiCountA) {
        return;
    }
    pikiCountB = pikiCountA;
    return;
}

/*
 * --INFO--
 * Address:	80119D2C
 * Size:	000010
 */

void PikiInfo::subFormationPiki(void) {
	BUMP_REGISTER(r4);
	pikiCountA--;
}

// extern PikiInfo* pikiInfo;
