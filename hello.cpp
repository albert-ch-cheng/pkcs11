
#include <stdio.h>
#include <stdlib.h>
#include "cryptoki.h" 

int main(int argc, char* argv[]) {
    CK_RV rv;
    unsigned long slotCnt = 0;
    CK_SLOT_ID_PTR pSlots;
    CK_SLOT_INFO   SlotInfo;

    printf ("Hello world!\n");
    rv = C_Initialize(NULL_PTR);
    if (rv!= CKR_OK) {
        printf ("C_Initialize() fails!\n");
        return 0;
    } else   
        printf ("C_Initialize ok!\n");

    // prepare slot information
    rv = C_GetSlotList (CK_FALSE,NULL_PTR, &slotCnt);
    if (rv==CKR_OK) {
        printf ("available slots = %lu\n",slotCnt);
        pSlots = (CK_SLOT_ID_PTR)malloc(sizeof(CK_SLOT_ID)*slotCnt);
        if (pSlots) {
            rv = C_GetSlotList (CK_FALSE,pSlots,&slotCnt);
            if (rv==CKR_OK) {
                printf ("Slot ID = %lx\n",*(unsigned long*)pSlots);
            }       
            rv = C_GetSlotInfo (*pSlots,&SlotInfo);
            if (rv==CKR_OK) {
                printf ("> Slot description = %s\n",SlotInfo.slotDescription);
                printf ("> Slot manufactureID = %s\n", SlotInfo.manufacturerID);
                printf ("> Slot hardware version = (%d.%d)\n",SlotInfo.hardwareVersion.major, SlotInfo.hardwareVersion.minor);
            } else {
                printf ("Cannot get the details of Slot(ID=%lx)\n",*(unsigned long*)pSlots);
            }
        } else {
            printf ("malloc() error\n");
        }
    }
    if (!pSlots) free (pSlots);    
    C_Finalize (NULL_PTR);
}

