#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#include ".\i18n.h"
#include ".\DataOfRanger1_jp.h"
#include ".\DataOfRanger2.h"
#include ".\DataOfRanger3_jp.h"
#include ".\DataOfRanger3_oversea.h"

void insertData(const char *filename, const unsigned char *data, size_t dataSize, long position, int ToolLanguage);
int crc16_table[];
unsigned int CRC16(char *data, int size);
void ChunkCrypt(unsigned int *data, int size);
void CryptRanger1(const char *filename,int ToolLanguage);
unsigned char GetR1Flag(const char *filename, unsigned int FlagType,int ToolLanguage);
unsigned int DistributeRanger1jpMission(const char *filename,int ToolLanguage);
unsigned int DistributeRanger23Mission(const char *filename,char initGameMark[],unsigned int BaseOffset,unsigned int BlockSize,const unsigned char *const Mission[],unsigned char BlockSet[],int ToolLanguage);
void CreateInitialSave(int ToolLanguage,int InitialSaveType);
unsigned int RNG();
unsigned int GenerateR1Seed();
unsigned int GenerateR1Time(const char *filename,int ToolLanguage);
unsigned short GenerateR1Date(const char *filename,int ToolLanguage);
unsigned int ManaphyMissionReset(const char *filename,int ToolLanguage);

#define GAME_VERSION_RANGER1  1
#define GAME_VERSION_RANGER2  2
#define GAME_VERSION_RANGER3  3

#define GAME_LANGUAGE_JP      1
#define GAME_LANGUAGE_OVERSEA 2
#define GAME_LANGUAGE_US_EN   3
#define GAME_LANGUAGE_EU_EN   4
#define GAME_LANGUAGE_EU_FR   5
#define GAME_LANGUAGE_EU_IT   6
#define GAME_LANGUAGE_EU_DE   7
#define GAME_LANGUAGE_EU_SP   8

int main(int argc, char *argv[]) 
{
    //system("chcp 65001");
    printf("*-------------------------------------------------------------*\n");
    printf("| ������Ѳ��Ա�������������� v1.0            �����Կ�΢������ |\n");
    printf("| PokemonRangerNetMissionDistributionTool v1.0 made by wokann |\n");
    printf("|                                                  2023.12.18 |\n");
    printf("*-------------------------------------------------------------*\n\n");
    
    int ToolLanguage = -1;
    while(1)
    {
        for(int i = 0; i < TOOL_LANGUAGE_COUNTS;i++)
        {
            //��ʾ��ʾ���뱾���ߵ���ʾ����
            printf(TextOfPRNMDTool[i][0]);
        }
        printf(":");
        scanf("%d", &ToolLanguage);
        getchar();
        if(ToolLanguage > 0 && ToolLanguage <= TOOL_LANGUAGE_COUNTS)
        {
            ToolLanguage--;
            printf("*------------------------------------------------*\n\n");
            break;
        }
        else
        {        
            for(int i = 0; i < TOOL_LANGUAGE_COUNTS;i++)
            {
                //��ʾ��������
                printf(TextOfPRNMDTool[i][1]);
            }
            printf("\n");
        }
    }
    int IfMakeInitialSave = 0;
    int InitialSaveType = -1;
    if(argc < 2)
    {
        while(1)
        {
            printf("*------------------------------------------------*\n");
            //��ʾʹ�÷���
            printf(TextOfPRNMDTool[ToolLanguage][2]);
            //��ʾ�Ƿ񴴽���ʼ�浵
            printf(TextOfPRNMDTool[ToolLanguage][60]);
            scanf("%d", &IfMakeInitialSave);
            getchar();
            if(IfMakeInitialSave == 1)
            {
                //��ʾ��ʼ�浵����
                printf(TextOfPRNMDTool[ToolLanguage][61]);
                scanf("%d", &InitialSaveType);
                getchar();
                while(1)
                {
                    if(InitialSaveType>=1 && InitialSaveType <=4)
                    {
                        InitialSaveType--;
                        CreateInitialSave(ToolLanguage,InitialSaveType);
                        //��ʾ�Ƿ����������ʼ�浵
                        printf(TextOfPRNMDTool[ToolLanguage][68]);
                        scanf("%d", &IfMakeInitialSave);
                        getchar();
                        printf("\n");
                        if(IfMakeInitialSave == 1)
                            break;
                        else if(IfMakeInitialSave == 2)
                        {
                            //��ʾ���س��˳�
                            printf(TextOfPRNMDTool[ToolLanguage][3]);
                            getchar(); // �ȴ��û����»س���
                            return 1;
                        }
                        else
                        {
                            //��ʾ��������
                            printf(TextOfPRNMDTool[ToolLanguage][1]);
                            printf("\n");
                            break;
                        }
                    }
                    else
                    {
                        //��ʾ��������
                        printf(TextOfPRNMDTool[ToolLanguage][1]);
                        printf("\n");
                        break;
                    }
                }
            }
            else if(IfMakeInitialSave == 2)
            {
                //��ʾ���س��˳�
                printf(TextOfPRNMDTool[ToolLanguage][3]);
                getchar(); // �ȴ��û����»س���
                return 1;
            }
            else
            {
                //��ʾ��������
                printf(TextOfPRNMDTool[ToolLanguage][1]);
                printf("\n");
            }
        }
    }
    //��ʾ���δ����ı�����
    printf(TextOfPRNMDTool[ToolLanguage][4],argc - 1);
    unsigned int IsR1OverseaExisted = false;
    for(int i = 1; i < argc; i++)
    {   
        //��ʾ��ǰ�ı����
        printf(TextOfPRNMDTool[ToolLanguage][5],i);
        //��ȡ�浵�ļ����������� "Distributed_"+ԭ�� ������ļ�
        const char *originfilename  = argv[i];
        //��ʾԭ�ļ���
        printf(TextOfPRNMDTool[ToolLanguage][6],originfilename);
        char newfilename[65535];
        memset(newfilename, 0, sizeof(newfilename));
        const char *lastSlash = strrchr(originfilename, '\\');// �ҵ�·�������һ����б�ܵ�λ��
        if (lastSlash != NULL) 
        {
            int position = lastSlash - originfilename;// ��ȡ·��ĩβ������λ��
            strncpy(newfilename, originfilename, position + 1); // ����·�����ݵ����ļ������������ķ�б�ܣ�
            strcat(newfilename, TextOfPRNMDTool[ToolLanguage][7]); // ��·������׷��ǰ׺
            strcat(newfilename, lastSlash + 1);// ׷��ԭʼ�ļ�������������б�ܣ�
        }
        else    // ���δ�ҵ���б�ܣ���ֱ�����ļ���ǰ����ǰ׺
        {
            strcpy(newfilename, TextOfPRNMDTool[ToolLanguage][7]);
            strcat(newfilename, originfilename);
        }
        //����ԭ�ļ�������ļ�
        FILE *originalFile, *newFile;
        originalFile = fopen(originfilename, "rb");
        if (originalFile == NULL) 
        {   
            //��ʾ�޷����ļ�
            printf(TextOfPRNMDTool[ToolLanguage][8],originfilename);
            //��ʾ���ļ��������
            printf(TextOfPRNMDTool[ToolLanguage][9],i);
            continue;
        }
        newFile = fopen(newfilename, "wb");
        if (newFile == NULL) 
        {
            //��ʾ�޷�����ļ�
            printf(TextOfPRNMDTool[ToolLanguage][10],originfilename);
            //��ʾ���ļ��������
            printf(TextOfPRNMDTool[ToolLanguage][9],i);
            continue;
        }
        char buffer[1024];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), originalFile)) > 0) 
        {
            fwrite(buffer, 1, bytesRead, newFile);
        }
        fclose(originalFile);
        fclose(newFile);

        //��ȡ�ļ�ͷ���жϰ汾������
        unsigned char gGameVersion = 0;
        unsigned char gGameLanguage = 0;
        char *gGameMark = (char *)malloc(8);
        char *gGameMarkR1_2 = (char *)malloc(4);
        unsigned int *OffsetOfSave = (unsigned int *)malloc(4);
        char initGameMarkR1_1[0x8] = {0x50,0x4B,0x52,0x2D,0x30,0x35,0x39,0x00}; //PKR-059/0
        char initGameMarkR1_2[0x4] = {0x61,0x30,0x30,0x00};                     //a00/0
        char initGameMarkR2[0x8] = {0x44,0x53,0x50,0x52,0x53,0x00,0x00,0x00};   //DSPRS/0/0/0
        char initGameMarkR3[0x8] = {0x44,0x53,0x52,0x41,0x53,0x41,0x00,0x00};   //DSRASA/0/0
        newFile = fopen(newfilename, "rb");
        fseek(newFile, 0, SEEK_SET);
        fread(gGameMark, 1, 8, newFile);
        fseek(newFile, 8, SEEK_SET);
        fread(gGameMarkR1_2, 1, 4, newFile);
        fseek(newFile, 8, SEEK_SET);
        fread(OffsetOfSave, 1, 4, newFile);
        fclose(newFile);
        if(!strcmp(gGameMark,initGameMarkR1_1) && !strcmp(gGameMarkR1_2,initGameMarkR1_2))
        {   
            gGameVersion = GAME_VERSION_RANGER1;
            CryptRanger1(newfilename,ToolLanguage);
            unsigned char LanguageFlag = GetR1Flag(newfilename,0x1B,ToolLanguage);
            if(LanguageFlag == 1)
                gGameLanguage = GAME_LANGUAGE_JP;
            else if(LanguageFlag >=2 && LanguageFlag <=6)
                gGameLanguage = GAME_LANGUAGE_OVERSEA;
            else
            {
                remove(newfilename);
                //��ʾr1�浵����
                printf(TextOfPRNMDTool[ToolLanguage][11]);
                //��ʾ���ļ��������
                printf(TextOfPRNMDTool[ToolLanguage][9],i);
                continue;
            }
        }
        else if(!strcmp(gGameMark,initGameMarkR2) && OffsetOfSave[0] == 0x1C)
        {
            gGameVersion = GAME_VERSION_RANGER2;
            gGameLanguage = GAME_LANGUAGE_JP;       //2�������ַ�հ溣�����ͬ��ѡ�������Ծ���
            //gGameLanguage = GAME_LANGUAGE_OVERSEA;  //2�������ַ�հ溣�����ͬ��ѡ�������Ծ���
        }
        else if(!strcmp(gGameMark,initGameMarkR3) && (OffsetOfSave[0] == 0x1C || OffsetOfSave[0] == 0x100))
        {
            gGameVersion = GAME_VERSION_RANGER3;
            if(OffsetOfSave[0] == 0x1C)
                gGameLanguage = GAME_LANGUAGE_JP;
            else if(OffsetOfSave[0] == 0x100)
                gGameLanguage = GAME_LANGUAGE_OVERSEA;
        }
        else
        {
            remove(newfilename);
            //��ʾr123�浵����
            printf(TextOfPRNMDTool[ToolLanguage][12]);
            //��ʾ���ļ��������
            printf(TextOfPRNMDTool[ToolLanguage][9],i);
            continue;;
        }
        if(gGameVersion != 2)
        {
            //��ʾ�浵��Ϸ�汾������
            printf(TextOfPRNMDTool[ToolLanguage][13 + gGameLanguage],gGameVersion);
        }
        else
        {
           //��ʾ�浵��Ϸ�汾������
            printf(TextOfPRNMDTool[ToolLanguage][13],gGameVersion);
        }
        
        //���ݰ汾�����Խ�������
        unsigned int HadDistributedCounts = 0;
        unsigned int HasResetManaphy = false;
        if(gGameVersion == GAME_VERSION_RANGER1)
        {
            if(gGameLanguage == GAME_LANGUAGE_JP)
            {   
                HadDistributedCounts = DistributeRanger1jpMission(newfilename,ToolLanguage);
                HasResetManaphy = ManaphyMissionReset(newfilename,ToolLanguage);
                CryptRanger1(newfilename,ToolLanguage);
            }
            else if(gGameLanguage == GAME_LANGUAGE_OVERSEA)
            {
                IsR1OverseaExisted = true;
                //��ʾѲ��Ա1���������˵��
                printf(TextOfPRNMDTool[ToolLanguage][35]);
                HasResetManaphy = ManaphyMissionReset(newfilename,ToolLanguage);
                CryptRanger1(newfilename,ToolLanguage);
            }
        }
        else if(gGameVersion == GAME_VERSION_RANGER2)
        { 
            unsigned char BlockSet[6] = {0,1,2,3,4,5};
            if(gGameLanguage == GAME_LANGUAGE_JP||gGameLanguage == GAME_LANGUAGE_OVERSEA)
                HadDistributedCounts = DistributeRanger23Mission(newfilename,initGameMarkR2,0x1BDBE,0x3020,Ranger2Mission,BlockSet,ToolLanguage);
        }
        else if(gGameVersion == GAME_VERSION_RANGER3)
        {   
            unsigned char BlockSet[6] = {0,1,2,3,4,6};
            if(gGameLanguage == GAME_LANGUAGE_JP)
                HadDistributedCounts = DistributeRanger23Mission(newfilename,initGameMarkR3,0x1A4BC,0x401C,Ranger3jpMission,BlockSet,ToolLanguage);
            else if(gGameLanguage == GAME_LANGUAGE_OVERSEA)
                HadDistributedCounts = DistributeRanger23Mission(newfilename,initGameMarkR3,0x1A900,0x4100,Ranger3overseaMission,BlockSet,ToolLanguage);
        }
        //ȷ���Ƿ���Ҫ��������������ļ�
        if((gGameVersion == GAME_VERSION_RANGER1 && gGameLanguage == GAME_LANGUAGE_JP && HadDistributedCounts == 4 && HasResetManaphy == false)||
           (gGameVersion == GAME_VERSION_RANGER1 && gGameLanguage == GAME_LANGUAGE_OVERSEA && HasResetManaphy == false)||
           (gGameVersion == GAME_VERSION_RANGER2 && HadDistributedCounts == 6)||
           (gGameVersion == GAME_VERSION_RANGER3 && HadDistributedCounts == 6))
        {
            remove(newfilename);
            //��ʾ�ļ���������
            printf(TextOfPRNMDTool[ToolLanguage][22]);
        }
        else
            //��ʾ����ļ���
            printf(TextOfPRNMDTool[ToolLanguage][23],newfilename);
        //��ʾ���ļ��������
        printf(TextOfPRNMDTool[ToolLanguage][9],i);
    }
    //��ʾ�����ļ��������
    printf(TextOfPRNMDTool[ToolLanguage][24], argc - 1);
    if(IsR1OverseaExisted == true)
    {
        //��ʾ����1������棬������˵��
        printf(TextOfPRNMDTool[ToolLanguage][25]);
    }
    //��ʾ�˳�����
    printf(TextOfPRNMDTool[ToolLanguage][3]);
    getchar(); // �ȴ��û����»س���
    return 0;
}

// �������ݵ��ļ��ĺ���
void insertData(const char *filename, const unsigned char *data, size_t dataSize, long position, int ToolLanguage) 
{
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) 
    {
        //��ʾ�޷����ļ�
        printf(TextOfPRNMDTool[ToolLanguage][26]);
        return;
    }
    // �ƶ��ļ�ָ�뵽�ض�λ��
    fseek(file, position, SEEK_SET);
    // д��Ҫ��������ݣ����ǣ�
    fwrite(data, 1, dataSize, file);
    // �ر��ļ�
    fclose(file);
}

unsigned char GetR1Flag(const char *filename, unsigned int FlagType,int ToolLanguage)
{
    FILE *sav = fopen(filename, "rb");
    if (sav == NULL) 
    {
        //��ʾ�޷����ļ�
        printf(TextOfPRNMDTool[ToolLanguage][26]);
        return 0;
    }
    unsigned int *dataSize = (unsigned int *)malloc(4);
    unsigned int *siskintsdChunkOffset = (unsigned int *)malloc(4);
    unsigned char *Flag = (unsigned char *)malloc(1);
    unsigned char *tmp = (unsigned char *)malloc(1);
    for(int i = 0; i < 10; i++)
    {
        fseek(sav,0x44 + i * 0x30,SEEK_SET);
        fread(dataSize, 1, 4, sav);
        if(dataSize[0] == 0x260C)
        {
            fseek(sav,0x40 + i * 0x30,SEEK_SET);
            fread(siskintsdChunkOffset, 1, 4, sav);
            break;
        }
    }
    fseek(sav,siskintsdChunkOffset[0] + 0x10,SEEK_SET);
    fread(Flag, 1, 1, sav);
    fseek(sav,siskintsdChunkOffset[0] + 0x2710,SEEK_SET);
    fread(tmp, 1, 1, sav);
    if(tmp[0]>Flag[0] && tmp[0]!=0xFF && Flag[0] !=0xFF)
    {
        fseek(sav,siskintsdChunkOffset[0] + FlagType + 0x2700,SEEK_SET);
        fread(Flag, 1, 1, sav);
    }
    else if(tmp[0]<=Flag[0] && tmp[0]!=0xFF && Flag[0] !=0xFF)
    {
        fseek(sav,siskintsdChunkOffset[0] + FlagType,SEEK_SET);
        fread(Flag, 1, 1, sav);
    }
    else if(tmp[0] == 0xFF)
    {
        fseek(sav,siskintsdChunkOffset[0] + FlagType,SEEK_SET);
        fread(Flag, 1, 1, sav);
    }
    else if(Flag[0] == 0xFF)
    {    
        fseek(sav,siskintsdChunkOffset[0] + FlagType + 0x2700,SEEK_SET);
        fread(Flag, 1, 1, sav);
    }
    fclose(sav);
    return Flag[0];
}

int crc16_table[] =
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

unsigned int CRC16(char *data, int size)
{
    unsigned int chk = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        chk = (crc16_table[(data[i] ^ chk) & 0xFF] ^ chk >> 8);
    }
    return chk;
}

void ChunkCrypt(unsigned int *data, int size)
{
    int i;                          // r5
    unsigned int rand;              // ST04_4
    unsigned int h_rand;            // r0
    unsigned int s_rand = data[0];  // the initial seed is located before the encrypted data

    for(i = 1; i < (size/4); i++)
    {
        rand = 0x5D588B65 * s_rand;
        h_rand = rand;
        s_rand = 0x5D588B65 * rand;
        data[i] ^= (h_rand & 0xFFFF0000) | (s_rand >> 16);
    }
}

void CryptRanger1(const char *filename,int ToolLanguage)
{
    FILE *sav = fopen(filename, "rb+");
    if (sav == NULL) 
    {
        //��ʾ�޷����ļ�
        printf(TextOfPRNMDTool[ToolLanguage][26]);
        return;
    }

    //��ȡ�浵��ǰ�ӽ���״̬
    char IsEncrypted = true;//Ĭ�ϼٶ�Ϊ����״̬
    unsigned int *maxChunkCounts = (unsigned int *)malloc(0x4);
    fseek(sav,0x1C,SEEK_SET);
    fread(maxChunkCounts, 1, 4, sav);
    if(maxChunkCounts[0] == 10)
        IsEncrypted = false;//����״̬
    free(maxChunkCounts);

    //��ȡ���ܵĴ浵ͷ���ݣ������浵��ʶ���������ں������������
    unsigned int *DecryptedHeader = (unsigned int *)malloc((R1JP_SAVE_HEADER_SIZE-0xC));
    fseek(sav, 0xC, SEEK_SET);
    fread(DecryptedHeader, 1, (R1JP_SAVE_HEADER_SIZE-0xC), sav);
    if(IsEncrypted)
        ChunkCrypt(DecryptedHeader, (R1JP_SAVE_HEADER_SIZE-0xC));
    
    //�ӽ����ļ�ͷ��������
    //��ͷ�������ļ�ͷ��������Ӧ������ȫһ�µľ��񱸷�
    for(int i = 0; i < 2;i++)
    {
        unsigned int *R1JPSaveheader = (unsigned int *)malloc((R1JP_SAVE_HEADER_SIZE-0xC));
        fseek(sav, 0xC + (R1JP_SAVE_HEADER_SIZE*i), SEEK_SET);
        fread(R1JPSaveheader, 1, (R1JP_SAVE_HEADER_SIZE-0xC), sav);
        if(!IsEncrypted)//����״̬������crc16
            R1JPSaveheader[1] = CRC16((char*)R1JPSaveheader+0x8, (R1JP_SAVE_HEADER_SIZE-0xC-0x8));
        ChunkCrypt(R1JPSaveheader, (R1JP_SAVE_HEADER_SIZE-0xC));
        fseek(sav, 0xC + (R1JP_SAVE_HEADER_SIZE*i), SEEK_SET);
        fwrite(R1JPSaveheader, 1, (R1JP_SAVE_HEADER_SIZE-0xC), sav);
        free(R1JPSaveheader);
    }

    //�ӽ���ʣ��Ŀ�
    //��������3(����)+7(����λ)=10�飬ʵ�����3+4(����)=7��
    //siskin.tsd, wren.tsd, hazel.tsd,
    //set_delivery001.dat, set_delivery003.dat, set_delivery002.dat, set_delivery004.dat
    //�������siskin.tsdλ�ڵ�1λ��ʣ��鰴��Ϸ�����ɺͽ������ŵ��Ⱥ��ϵȷ��ʵ��˳��
    //��ȷ������û�н�����ȥ���ţ��Ƿ�Ὣsiskin.tsd�Ӻ�
    int existedChunk = 0;
    for(int i = 0; i < 10; i++)
    {
        unsigned int datasize = DecryptedHeader[0xE + (i*0xC)];
        if(datasize)
            existedChunk++;
    }
    for(int i = 0; i < existedChunk; i++)
    {
        unsigned int subChunkCounts = DecryptedHeader[0xC + (i*0xC)] >> 16 & 0xFF;
        unsigned int chunkOffset = DecryptedHeader[0xD + (i*0xC)];
        unsigned int dataSize = DecryptedHeader[0xE + (i*0xC)];
        unsigned int subChunkSize = DecryptedHeader[0xF + (i*0xC)] / subChunkCounts;

        if(chunkOffset != 0)
        {
            unsigned int j;
            for(j = 0; (j < subChunkCounts) && (j < 3); j++)
            {
                unsigned int *subchunk = (unsigned int *)malloc(subChunkSize);
                fseek(sav, chunkOffset + (subChunkSize*j), SEEK_SET);
                fread(subchunk, 1, subChunkSize, sav);
                if(!IsEncrypted && ((subchunk[1] & 0xFFFF) != 0))//����״̬������crc16����ԭcrc��Ϊ0���жϴ浵ʹ�ý�����crc16Ϊ0��
                    subchunk[1] = CRC16((char*)subchunk+0x18, dataSize);
                ChunkCrypt(subchunk, (dataSize+0x18));
                fseek(sav, chunkOffset + (subChunkSize*j), SEEK_SET);
                fwrite(subchunk, 1, (dataSize+0x18), sav);
                free(subchunk);
            }
        }
        //unsigned int nowOffset = ftell(sav);
        //printf("��ǰ��ַΪ��%08x �ֽ�\n", nowOffset);
    } 
    free(DecryptedHeader);
	fclose(sav);
    return;
}

unsigned int DistributeRanger1jpMission(const char *filename,int ToolLanguage)
{
    FILE *sav = fopen(filename, "rb+");
    if (sav == NULL) 
    {
        //��ʾ�޷����ļ�
        printf(TextOfPRNMDTool[ToolLanguage][26]);
        return 0;
    }
    //��ȡ���ܵĴ浵ͷ���ݣ������浵��ʶ���������ں������������
    unsigned int *DecryptedHeader = (unsigned int *)malloc((R1JP_SAVE_HEADER_SIZE-0xC));
    fseek(sav, 0xC, SEEK_SET);
    fread(DecryptedHeader, 1, (R1JP_SAVE_HEADER_SIZE-0xC), sav);
    fclose(sav);
    //�������п������Լ��Ƿ���������ſ�
    int existedChunk = 0;
    unsigned int HadDistributedCounts = 0;
    char chunkOrder[7]=
    {
        [SISKIN] = 10,//siskin.tsd              datasize:0x260C chunksize:0x4E00
        [WREN]   = 10,//wren.tsd                datasize:0x30D4 chunksize:0x6200
        [HAZEL]  = 10,//hazel.tsd               datasize:0x30D4 chunksize:0x6200
        [D001]   = 10,//set_delivery001.dat     datasize:0xE7E8 chunksize:0xE800
        [D002]   = 10,//set_delivery003.dat     datasize:0x67E8 chunksize:0x6800
        [D003]   = 10,//set_delivery002.dat     datasize:0x57E8 chunksize:0x5800
        [D004]   = 10,//set_delivery004.dat     datasize:0x4FE8 chunksize:0x5000
    };
    for(int i = 0; i < 10; i++)
    {
        unsigned int dataSize = DecryptedHeader[0xE + (i*0xC)];
        unsigned char firstnNameChar = DecryptedHeader[0x5 + (i*0xC)];
        if(dataSize)
            existedChunk++;
        
        if(dataSize == 0x260C)
            chunkOrder[SISKIN]=i;
        else if(dataSize == 0x30D4 && firstnNameChar == 'w')
            chunkOrder[WREN]=i;
        else if(dataSize == 0x30D4 && firstnNameChar == 'h')
            chunkOrder[HAZEL]=i;
        else if(dataSize == 0xE7E8)
            chunkOrder[D001]=i;
        else if(dataSize == 0x67E8)
            chunkOrder[D002]=i;
        else if(dataSize == 0x57E8)
            chunkOrder[D003]=i;
        else if(dataSize == 0x4FE8)
            chunkOrder[D004]=i;
    }
    //�������п飬�ں󷽲�����������
    for(int i = 0;i < 4;i++)
    {
        unsigned int siskintsdChunkOffset = DecryptedHeader[0xD + (chunkOrder[SISKIN]*0xC)];
        unsigned char MissionNewFlag;
        if(chunkOrder[i+3] == 10)
        {
            unsigned int previousChunkOffset = DecryptedHeader[0xD + ((existedChunk-1)*0xC)];
            unsigned int previousChunkSize = DecryptedHeader[0xF + ((existedChunk-1)*0xC)];
            unsigned int NowChunkOffset = previousChunkOffset + previousChunkSize;

            //д��saveheader
            insertData(filename, SaveHeaderOfD00[i], 0x30, 0x20 + (existedChunk*0x30),ToolLanguage);
            insertData(filename, SaveHeaderOfD00[i], 0x30, 0x20 + (existedChunk*0x30) + 0x200,ToolLanguage);
            //д��siskin.tsd����brief
            insertData(filename, BriefOfD00[i], 0x56C, siskintsdChunkOffset + 0x30 + i*0x56C,ToolLanguage);
            insertData(filename, BriefOfD00[i], 0x56C, siskintsdChunkOffset + 0x30 + i*0x56C + 0x2700,ToolLanguage);
            //д����chunk
            insertData(filename, DataOfD00[i], ChunkSizeOfD00[i], NowChunkOffset,ToolLanguage);

            //����saveheader��chunkƫ�Ƶ�ַ
            FILE *sav = fopen(filename, "rb+");
            fseek(sav, (0x40 + (existedChunk*0x30)), SEEK_SET);
            fwrite(&NowChunkOffset, 1, 4, sav);
            fseek(sav, (0x240 + (existedChunk*0x30)), SEEK_SET);
            fwrite(&NowChunkOffset, 1, 4, sav);
            //����siskin.tsd��new mission flag
            fseek(sav,siskintsdChunkOffset + 0x22,SEEK_SET);
            MissionNewFlag = fgetc(sav);
            MissionNewFlag = MissionNewFlag | (1<<i);
            fseek(sav,siskintsdChunkOffset + 0x22,SEEK_SET);
            fwrite(&MissionNewFlag, 1, 1, sav);
            //siskin.tsd2
            fseek(sav,siskintsdChunkOffset + 0x2722,SEEK_SET);
            MissionNewFlag = fgetc(sav);
            MissionNewFlag = MissionNewFlag | (1<<i);
            fseek(sav,siskintsdChunkOffset + 0x2722,SEEK_SET);
            fwrite(&MissionNewFlag, 1, 1, sav);

            //����DecryptedHeader
            fseek(sav, 0xC, SEEK_SET);
            fread(DecryptedHeader, 1, (R1JP_SAVE_HEADER_SIZE-0xC), sav);
            fclose(sav);

            chunkOrder[i+3] = existedChunk;
            existedChunk++;
            //��ʾ�����������
            printf(TextOfPRNMDTool[ToolLanguage][27+i]);
        }
        else
        {
            HadDistributedCounts++;
            //��ʾ�����ѽ�����������
            printf(TextOfPRNMDTool[ToolLanguage][31+i]);
        }
    }
    free(DecryptedHeader);
    return HadDistributedCounts;
}

unsigned int DistributeRanger23Mission(const char *filename,char initGameMark[],unsigned int BaseOffset,unsigned int BlockSize,const unsigned char *const Mission[],unsigned char BlockSet[],int ToolLanguage)
{    FILE *file = fopen(filename, "rb");    
    if (file == NULL) 
    {
        //��ʾ�޷����ļ�
        printf(TextOfPRNMDTool[ToolLanguage][26]);
        return 0;
    }
    //��ʼĬ�ϲ�����
    char *gGameMark = (char *)malloc(8);
    unsigned int HadDistributedCounts = 0;
    for(int i = 0; i < 6; i++)
    {   //����Ƿ��Ѿ���������
        memset(gGameMark, 0, 8);
        fseek(file, (BaseOffset + BlockSize * BlockSet[i]), SEEK_SET);
        fread(gGameMark, 1, 8, file);
        int TextNumber = (strlen(initGameMark)-5)*12;
        if(!strcmp(gGameMark,initGameMark))
        {
            //��ʾ�����ѽ�����������
            printf(TextOfPRNMDTool[ToolLanguage][42+TextNumber+i]);
            HadDistributedCounts++;
        }
        else
        {
            //��ʾ�����������
            insertData(filename, Mission[i], BlockSize, (BaseOffset + BlockSize * BlockSet[i]),ToolLanguage);
            printf(TextOfPRNMDTool[ToolLanguage][36+TextNumber+i]);
        }
    }
    free(gGameMark);
    fclose(file);
    return HadDistributedCounts;
}

void CreateInitialSave(int ToolLanguage,int InitialSaveType)
{
    #define RANGER1_JP      0
    #define RANGER2         1
    #define RANGER3_JP      2
    #define RANGER3_OVERSEA 3
    const char *Initialfilename  = TextOfPRNMDTool[ToolLanguage][62+InitialSaveType];
    FILE *file = fopen(Initialfilename, "wb");
    if (file == NULL) 
    {
        //��ʾ�޷������ļ�
        printf(TextOfPRNMDTool[ToolLanguage][66]);
        return;
    }
    //���0xFF
    char *buffer;
    buffer = (char *)malloc(0x40000);
    for (int i = 0; i < 0x40000; i++) 
        buffer[i] = 0xFF;
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, 0x40000, file);
    free(buffer);
    fclose(file);

    //ȷ���汾������
    unsigned char gGameVersion = 0;
    unsigned char gGameLanguage = 0;
    switch(InitialSaveType)
    {
        case RANGER1_JP:
            gGameVersion = GAME_VERSION_RANGER1;
            break;
        case RANGER2:
            gGameVersion = GAME_VERSION_RANGER2;
            break;
        case RANGER3_JP:
            gGameVersion = GAME_VERSION_RANGER3;
            gGameLanguage = GAME_LANGUAGE_JP;
            break;
        case RANGER3_OVERSEA:
            gGameVersion = GAME_VERSION_RANGER3;
            gGameLanguage = GAME_LANGUAGE_OVERSEA;
            break;
    }
    //���ݰ汾�����Խ�������
    char initGameMarkR2[0x8] = {0x44,0x53,0x50,0x52,0x53,0x00,0x00,0x00};   //DSPRS/0/0/0
    char initGameMarkR3[0x8] = {0x44,0x53,0x52,0x41,0x53,0x41,0x00,0x00};   //DSRASA/0/0
    if(gGameVersion == GAME_VERSION_RANGER1)
    {
        file = fopen(Initialfilename, "rb+");
        buffer = (char *)malloc(0x260C);
        for (int i = 0; i < 0x260C; i++) 
            buffer[i] = 0x00;
        fseek(file, 0, SEEK_SET);
        //00���header��2����
        fwrite(buffer, 1, 0x400, file);
        //00���siskintsd�ĵ�2����
        fseek(file, 0x2B00, SEEK_SET);
        fwrite(buffer, 1, 0x260C, file);
        free(buffer);
        fclose(file);
        //���Ԥ��saveheader
        insertData(Initialfilename, InititalSaveTemplate[0], 0xB0, 0,ToolLanguage);
        insertData(Initialfilename, InititalSaveTemplate[0], 0xB0, 0x200,ToolLanguage);
        //���Ԥ��siskintsd
        insertData(Initialfilename, InititalSaveTemplate[1], 0x8, 0x400,ToolLanguage);
        insertData(Initialfilename, InititalSaveTemplate[2], 0x30, 0x2B00,ToolLanguage);
        file = fopen(Initialfilename, "rb+");
        fseek(file, 0x2B28, SEEK_SET);
        unsigned int playerId = RNG();
        fwrite(&playerId, 1, 4, file);
        fclose(file);
        //���Ԥ��wrentsd
        insertData(Initialfilename, InititalSaveTemplate[3], 0x3100, 0x5200,ToolLanguage);
        insertData(Initialfilename, InititalSaveTemplate[4], 0x3100, 0x8300,ToolLanguage);
        //���Ԥ��hazeltsd
        insertData(Initialfilename, InititalSaveTemplate[5], 0x8, 0xB400,ToolLanguage);
        insertData(Initialfilename, InititalSaveTemplate[6], 0x3100, 0xE500,ToolLanguage);
        DistributeRanger1jpMission(Initialfilename,ToolLanguage); 
        CryptRanger1(Initialfilename,ToolLanguage);
    }
    else if(gGameVersion == GAME_VERSION_RANGER2)
    { 
        unsigned char BlockSet[6] = {0,1,2,3,4,5};
        DistributeRanger23Mission(Initialfilename,initGameMarkR2,0x1BDBE,0x3020,Ranger2Mission,BlockSet,ToolLanguage);
    }
    else if(gGameVersion == GAME_VERSION_RANGER3)
    {   
        unsigned char BlockSet[6] = {0,1,2,3,4,6};
        if(gGameLanguage == GAME_LANGUAGE_JP)
            DistributeRanger23Mission(Initialfilename,initGameMarkR3,0x1A4BC,0x401C,Ranger3jpMission,BlockSet,ToolLanguage);
        else if(gGameLanguage == GAME_LANGUAGE_OVERSEA)
            DistributeRanger23Mission(Initialfilename,initGameMarkR3,0x1A900,0x4100,Ranger3overseaMission,BlockSet,ToolLanguage);
    }
    //��ʾ��ʼ�浵�Ѵ���
    printf(TextOfPRNMDTool[ToolLanguage][67],Initialfilename);
}

unsigned int RNG() 
{
    //����Ǳ�����Ϊ�˽���ʼ�հ�浵�ڵ����id����������Ĵ�ʩ����������Ϸ�еļ��ܷ�ʽ��
    srand((unsigned int)time(NULL));  // ʹ�õ�ǰʱ����Ϊ���������
    unsigned int random = 0;
    for (int i = 0; i < 4; i++) 
        random = (random << 8) | (rand() & 0xFF);
    return random;
}

unsigned int GenerateR1Seed() 
{
    //NDSϵͳ
    #define REG_TM0D 0x04000100
    #define REG_TM0CNT 0x04000102
    //������Ϸ�е�seed���㣬���ǣ�
    //the seeds for the encryption is created by via timer 0 (REG_TM0D) + a counter of its overflow (REG_TM0CNT = TIMER_ON | TM_IRQ | TM_FREQ_64).
    //(REG_TM0D | (TM_IRQ_count << 16)) + 1
    //����@ajxpk���о�

    // �� timer 0 ��ȡ��ʼ seed
    uint16_t tm0d = *(volatile uint16_t*)REG_TM0D; // �ӼĴ�����ȡ timer 0 ��ֵ
    uint16_t tm0cnt = *(volatile uint16_t*)REG_TM0CNT; // �ӼĴ�����ȡ timer 0 ���ƼĴ�����ֵ
    uint32_t tm0Seed = (uint32_t)tm0d | ((uint32_t)tm0cnt << 16); // ��� timer 0 ��ֵ�Ϳ��ƼĴ�����ֵ

    // �� seed ���д���+1�����߽�������������
    uint32_t seed = tm0Seed + 1; // �� seed ���д��������1

    return seed;
}

unsigned int GenerateR1Time(const char *filename,int ToolLanguage)
{
    #define MINUTE_OFFSET 16
    #define SECOND_OFFSET 6
    #define HOUR_OFFSET   0
    FILE *file = fopen(filename, "rb");    
    if (file == NULL) 
    {
        //��ʾ�޷����ļ�
        printf(TextOfPRNMDTool[ToolLanguage][26]);
        return 0;
    }
    // ��ȡ��ǰϵͳʱ��
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    // ��ȡ������ʱ������Ϣ
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    unsigned int time = 0xFFFFFFFF; // Ĭ��ֵ���������´�saveheader��chunkheader��ȡ
    time &= 0xFFE0FFFF;
    time |= ((hour & 0x1F) << HOUR_OFFSET);
    time &= 0xFFFFFFC0;
    time |= (minute & 0x3F);
    time &= 0xFFFFF03F;
    time |= ((second & 0x3F) << SECOND_OFFSET);

    return time;
}
unsigned short GenerateR1Date(const char *filename,int ToolLanguage)
{
    #define YEAR_OFFSET  7
    #define MONTH_OFFSET 4
    #define DAY_OFFSET   0
    FILE *file = fopen(filename, "rb");    
    if (file == NULL) 
    {
        //��ʾ�޷����ļ�
        printf(TextOfPRNMDTool[ToolLanguage][26]);
        return 0;
    }
    // ��ȡ��ǰϵͳʱ��
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    // ��ȡ������ʱ������Ϣ
    int year = localTime->tm_year + 1900; // �������� 1900
    int month = localTime->tm_mon + 1;    // �·ݴ� 0 ��ʼ
    int day = localTime->tm_mday;

    unsigned short date = 0xFFFF; // Ĭ��ֵ���������´�saveheader��chunkheader��ȡ
    date &= 0xFF80;
    date |= (year & 0x7F);
    date &= 0xF87F;
    date |= ((month & 0xF) << MONTH_OFFSET);
    date &= 0x7FF;
    date |= ((day & 0x1F) << DAY_OFFSET);

    return date;
}

unsigned int ManaphyMissionReset(const char *filename,int ToolLanguage)
{
    #define MANAPHY_STATUS_MISSION_NOT_GET      0
    #define MANAPHY_STATUS_EGG_NOT_RECEIVED     1
    #define MANAPHY_STATUS_EGG_RECEIVED         2
    #define MANAPHY_STATUS_EGG_SENT             3

    #define RESET_NOTHING                       0
    #define RESET_TO_EGG_NOT_RECEIVED           1
    #define RESET_TO_EGG_RECEIVED               2

    FILE *file = fopen(filename, "rb+");    
    if (file == NULL) 
    {
        //��ʾ�޷����ļ�
        printf(TextOfPRNMDTool[ToolLanguage][26]);
        return 0;
    }
    fclose(file);
    unsigned int HasResetManaphy = false;
    unsigned int ManaphyStatus = MANAPHY_STATUS_MISSION_NOT_GET;
    unsigned int ResetStatus = RESET_NOTHING;
    //��ȡ���flag
    unsigned char LanguageFlag = GetR1Flag(filename,0x1B,ToolLanguage);
    unsigned char ManaphyFlag = GetR1Flag(filename,0x20,ToolLanguage);
    unsigned int dateOfObtainManaphyEgg = 0;
    for(int i = 0;i < 4;i++)
    {
        unsigned char tmp = GetR1Flag(filename,0x24 + i,ToolLanguage);
        dateOfObtainManaphyEgg = dateOfObtainManaphyEgg | (tmp << (8*i));
    }
    //����flagȷ����ǰstatus
    if(LanguageFlag == 1)//�հ棬�հ��ʱ�����Ѿ�������ţ�����status 1-3
    {
        if(ManaphyFlag == 0 && dateOfObtainManaphyEgg == 0)
            ManaphyStatus = MANAPHY_STATUS_EGG_NOT_RECEIVED;
        else if(ManaphyFlag == 1 && dateOfObtainManaphyEgg != 0)
            ManaphyStatus = MANAPHY_STATUS_EGG_RECEIVED;
        else if(ManaphyFlag == 2 && dateOfObtainManaphyEgg != 0)
            ManaphyStatus = MANAPHY_STATUS_EGG_SENT;
    }
    else if(LanguageFlag >= 2 && LanguageFlag <= 6)//����棬�����status 0-4���п���
    {
        if(ManaphyFlag == 0 && dateOfObtainManaphyEgg == 0)
            ManaphyStatus = MANAPHY_STATUS_MISSION_NOT_GET;
        else if(ManaphyFlag == 3 && dateOfObtainManaphyEgg == 0)
            ManaphyStatus = MANAPHY_STATUS_EGG_NOT_RECEIVED;
        else if(ManaphyFlag == 1 && dateOfObtainManaphyEgg != 0)
            ManaphyStatus = MANAPHY_STATUS_EGG_RECEIVED;
        else if(ManaphyFlag == 2 && dateOfObtainManaphyEgg != 0)
            ManaphyStatus = MANAPHY_STATUS_EGG_SENT;
    }
    //����status2��3���������ȡѡ����������
    if(ManaphyStatus == MANAPHY_STATUS_EGG_RECEIVED)
    {
        while(1)
        {
            //��ʾ�ѽ��յ�������ѡ��
            printf(TextOfPRNMDTool[ToolLanguage][69]);
            scanf("%d", &ResetStatus);
            getchar();
            if(ResetStatus == 1)
            {
                ResetStatus = RESET_TO_EGG_NOT_RECEIVED;
                break;
            }
            else if(ResetStatus == 2)
            {
                ResetStatus = RESET_NOTHING;
                break;
            }
            else
            {
                //��ʾ��������
                printf(TextOfPRNMDTool[ToolLanguage][1]);
                printf("\n");
            }
        }
    }
    else if( ManaphyStatus == MANAPHY_STATUS_EGG_SENT)
    {
        while(1)
        {
            //��ʾ�Ѵ��͵�������ѡ��
            printf(TextOfPRNMDTool[ToolLanguage][70]);
            scanf("%d", &ResetStatus);
            getchar();
            if(ResetStatus == 1)
            {
                ResetStatus = RESET_TO_EGG_NOT_RECEIVED;
                break;
            }
            else if(ResetStatus == 2)
            {
                ResetStatus = RESET_TO_EGG_RECEIVED;
                break;
            }
            else if(ResetStatus == 3)
            {
                ResetStatus = RESET_NOTHING;
                break;
            }
            else
            {
                //��ʾ��������
                printf(TextOfPRNMDTool[ToolLanguage][1]);
                printf("\n");
            }
        }
    }
    //��������ѡ���������
    file = fopen(filename, "rb+");
    unsigned int *dataSize = (unsigned int *)malloc(4);
    unsigned int *siskintsdChunkOffset = (unsigned int *)malloc(4);
    for(int i = 0; i < 10; i++)
    {
        fseek(file,0x44 + i * 0x30,SEEK_SET);
        fread(dataSize, 1, 4, file);
        if(dataSize[0] == 0x260C)
        {
            fseek(file,0x40 + i * 0x30,SEEK_SET);
            fread(siskintsdChunkOffset, 1, 4, file);
            break;
        }
    }
    if(ResetStatus == RESET_TO_EGG_NOT_RECEIVED)
    {
        if(LanguageFlag == 1)
            ManaphyFlag = 0;
        else
            ManaphyFlag = 3;
        dateOfObtainManaphyEgg = 0;
        unsigned char MissionNewFlag;
        //����newflag
        fseek(file,siskintsdChunkOffset[0] + 0x22,SEEK_SET);
        MissionNewFlag = fgetc(file);
        MissionNewFlag = MissionNewFlag | 1;
        fseek(file,siskintsdChunkOffset[0] + 0x22,SEEK_SET);
        fwrite(&MissionNewFlag, 1, 1, file);
        fseek(file,siskintsdChunkOffset[0] + 0x2722,SEEK_SET);
        MissionNewFlag = fgetc(file);
        MissionNewFlag = MissionNewFlag | 1;
        fseek(file,siskintsdChunkOffset[0] + 0x2722,SEEK_SET);
        fwrite(&MissionNewFlag, 1, 1, file);
        //����������flag
        fseek(file,siskintsdChunkOffset[0] + 0x20,SEEK_SET);
        fwrite(&ManaphyFlag,1,1,file);
        fseek(file,siskintsdChunkOffset[0] + 0x2720,SEEK_SET);
        fwrite(&ManaphyFlag,1,1,file);
        //���û�õ�����
        fseek(file,siskintsdChunkOffset[0] + 0x24,SEEK_SET);
        fwrite(&dateOfObtainManaphyEgg,1,4,file);
        fseek(file,siskintsdChunkOffset[0] + 0x2724,SEEK_SET); 
        fwrite(&dateOfObtainManaphyEgg,1,4,file);
        //��ʾ������Ϊδ���յ�
        printf(TextOfPRNMDTool[ToolLanguage][71]);
        //��ʾ������ͨ����ʾ
        printf(TextOfPRNMDTool[ToolLanguage][73]);
        HasResetManaphy = true;
    }
    else if(ResetStatus == RESET_TO_EGG_RECEIVED)
    {
        ManaphyFlag = 1;
        //����������flag
        fseek(file,siskintsdChunkOffset[0] + 0x20,SEEK_SET);
        fwrite(&ManaphyFlag,1,1,file);
        fseek(file,siskintsdChunkOffset[0] + 0x2720,SEEK_SET);
        fwrite(&ManaphyFlag,1,1,file);
        //��ʾ������Ϊδ���͵�
        printf(TextOfPRNMDTool[ToolLanguage][72]);
        //��ʾ������ͨ����ʾ
        printf(TextOfPRNMDTool[ToolLanguage][73]);
        HasResetManaphy = true;
    }
    fclose(file);
    return HasResetManaphy;
}
