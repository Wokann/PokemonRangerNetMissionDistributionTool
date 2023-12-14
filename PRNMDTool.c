#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include ".\DataOfRanger1_jp.h"
#include ".\DataOfRanger2.h"
#include ".\DataOfRanger3_jp.h"
#include ".\DataOfRanger3_oversea.h"
void insertData(const char *filename, const unsigned char *data, size_t dataSize, long position);
unsigned char IsStringExisted(const char *filename,char initGameMark[],unsigned char LengthOfGameMark,unsigned int SearchOffset);
int crc16_table[];
unsigned int CRC16(char *data, int size);
void RangerCrypt(unsigned int *data, int size);
void CryptRanger1jp(const char *filename);
void DistributeRanger1jpMission(const char *filename);
void DistributeRanger23Mission(const char *filename,char initGameMark[],unsigned char LengthOfGameMark,unsigned int BaseOffset,unsigned int BlockSize,const unsigned char *const Mission[],unsigned char BlockSet[]);

int main(int argc, char *argv[]) {
    //system("chcp 65001");
    printf("*-------------------------------------------------------------*\n");
    printf("| ������Ѳ��Ա�������������� v0.1            �����Կ�΢������ |\n");
    printf("| PokemonRangerNetMissionDistributionTool v0.1 made by wokann |\n");
    printf("|                                                  2023.12.10 |\n");
    printf("*-------------------------------------------------------------*\n\n");

    if (argc != 5) 
    {
        printf("���棺��������Ϸ�汾����Ϸ���ԡ��浵�������Ϊ�浵����\n");
        printf("�÷�: PRNMDTool.exe [-r1/-r2/-r3] [-jp/-oversea] [originfilename] [newfilename]\n\n");
        printf("Warning: Please input gameversion, gamelanguage, sav file name, new name you want to save sav file as.\n");
        printf("Usage: PRNMDTool.exe [-r1/-r2/-r3] [-jp/-oversea] [originfilename] [newfilename]\n");
        printf("\n\n���»س����˳�����...\n");
        printf("Press Enter to exit...\n");
        getchar(); // �ȴ��û����»س���
        return 1;
    }
    
    const char *GameVersion     = argv[1];
    const char *GameLanguage    = argv[2];
    const char *originfilename  = argv[3];
    const char *newfilename     = argv[4];
    //�������ļ�������ļ�
    FILE *originalFile, *newFile;
    originalFile = fopen(originfilename, "rb");
    if (originalFile == NULL) 
    {
        printf("�޷����ļ� \"%s\" ��\n�볢�������ļ��������������Ƴ��ļ����еĿո�\n\n", originfilename);
        printf("Can not open file \"%s\" .\nPlease try shortening the file name and removing spaces from the name.\n\n\n", originfilename);
        return 1;
    }
    newFile = fopen(newfilename, "wb");
    if (newFile == NULL) 
    {
        printf("�޷���������ļ� \"%s\" ��\n�볢�������ļ��������������Ƴ��ļ����еĿո�\n\n", newfilename);
        printf("Can not create new file \"%s\" .\nPlease try shortening the file name and removing spaces from the name.\n\n\n", newfilename);
        return 1;
    }
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), originalFile)) > 0) {
        fwrite(buffer, 1, bytesRead, newFile);
    }
    fclose(originalFile);
    fclose(newFile);

    //���ݰ汾�����Խ�������
    if(!strcmp(GameVersion, "-r1"))
    {
        if(!strcmp(GameLanguage, "-jp"))
        {   
            CryptRanger1jp(newfilename);
            //DistributeRanger1jpMission(newfilename);
            CryptRanger1jp(newfilename);
            printf("Ranger1-jp��4������������ɡ�\n����ļ� \"%s\" ��\n\n", newfilename);
            printf("4 missions of Ranger1-jp have been distributed.\nSee file \"%s\" .\n", newfilename);
        }
        else if(!strcmp(GameLanguage, "-oversea"))
        {
            printf("ע��Ѳ��Ա1�����������ͨ�����Ż�ȡ����\n");
            printf("����һ��Ŀͨ�غ��Զ�����3�����������������һ���������ܿ�����һ������\n");
            printf("����һ��Ŀͨ�غ���Ѳ��Ա������水�¡�R+X+LEFT���ɼ�����������ѡ�\n\n");
            printf("�������������������������ɿ�������������\n");
            printf("����*�����桡��������P8M2-9D6F-43H7\n");
            printf("����*ŷ��Ӣ�İ桡����Mg35-Cpb8-4FW8\n");
            printf("����*ŷ�޷��İ桡����DY4g-k28S-QB9F\n");
            printf("����*ŷ�޵��İ桡����R3d4-cv2S-WC7W\n");
            printf("����*ŷ���������İ棺C58f-t3WT-Vn79\n");
            printf("����*ŷ��������İ棺FH38-fwD8-5S2a\n\n\n");
            printf("Note: Ranger1 oversea don't need to be distributed mission.\n");
            printf("      After finishing the first game, Ranger Net will auto boot 3 missions, which you should finish the previous mission to unlock the next mission.\n");
            printf("      After finishing the first game, holding R+X+Left on the Ranger Net screen can unlock \"Enter the password\" option.\n\n");
            printf("      Then enter the code followed to unlock the Manaphy mission:\n");
            printf("      *US-en: P8M2-9D6F-43H7\n");
            printf("      *EU-en: Mg35-Cpb8-4FW8\n");
            printf("      *EU-fr: DY4g-k28S-QB9F\n");
            printf("      *EU-de: R3d4-cv2S-WC7W\n");
            printf("      *EU-sp: C58f-t3WT-Vn79\n");
            printf("      *EU-it: FH38-fwD8-5S2a\n");
            remove(newfilename);
        }
        else
        {
            printf("���棺�浵����Ӧ���룺[-jp] �� [-oversea]\n");
            printf("Warning: game language should input: [-jp] or [-oversea]\n");
            remove(newfilename);
        }
    }
    else if(!strcmp(GameVersion, "-r2"))
    { 
        if(!strcmp(GameLanguage, "-jp")||!strcmp(GameLanguage, "-oversea"))
        {
            char initGameMark[5] = {0x44,0x53,0x50,0x52,0x53}; //DSPRS
            unsigned char BlockSet[6] = {0,1,2,3,4,5};
            DistributeRanger23Mission(newfilename,initGameMark,5,0x1BDBE,0x3020,Ranger2Mission,BlockSet);
            printf("Ranger2��6������������ɡ�\n����ļ� \"%s\" ��\n\n", newfilename);
            printf("6 missions of Ranger2 have been distributed.\nSee file \"%s\" .\n", newfilename);
        }
        else
        {    
            printf("���棺�浵����Ӧ���룺[-jp] �� [-oversea]\n");
            printf("Warning: game language should input: [-jp] or [-oversea]\n");
            remove(newfilename);
        }
    }
    else if(!strcmp(GameVersion, "-r3"))
    {   
        char initGameMark[6] = {0x44,0x53,0x52,0x41,0x53,0x41}; //DSRASA
        unsigned char BlockSet[6] = {0,1,2,3,4,6};
        if(!strcmp(GameLanguage, "-jp"))
        {
            DistributeRanger23Mission(newfilename,initGameMark,6,0x1A4BC,0x401C,Ranger3jpMission,BlockSet);
            printf("Ranger3-jp��6������������ɡ�\n����ļ� \"%s\" ��\n\n", newfilename);
            printf("6 missions of Ranger3-jp have been distributed.\nSee file \"%s\" .\n", newfilename);
        }
        else if(!strcmp(GameLanguage, "-oversea"))
        {
            DistributeRanger23Mission(newfilename,initGameMark,6,0x1A900,0x4100,Ranger3overseaMission,BlockSet);
            printf("Ranger3-oversea��6������������ɡ�\n����ļ� \"%s\" ��\n\n", newfilename);
            printf("6 missions of Ranger3-oversea have been distributed.\nSee file \"%s\" .\n", newfilename);
        }
        else
        {
            printf("���棺�浵����Ӧ���룺[-jp] �� [-oversea]\n");
            printf("Warning: game language should input: [-jp] or [-oversea]\n");
            remove(newfilename);
        }
    }
    else
    {
        printf("���棺�浵�汾Ӧ���룺[-r1], [-r2], �� [-r3]\n");
        printf("Warning: game version should be: [-r1], [-r2] or [-r3]\n");
        remove(newfilename);
    }

    //printf("\n\n���»س����˳�����...\n");
    //printf("Press Enter to exit...\n");
    //getchar(); // �ȴ��û����»س���
    return 0;
}

// �������ݵ��ļ��ĺ���
void insertData(const char *filename, const unsigned char *data, size_t dataSize, long position) 
{
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) 
    {
        printf("�޷����ļ�\n");
        printf("Can not open file.\n\n");
        return;
    }
    // �ƶ��ļ�ָ�뵽�ض�λ��
    fseek(file, position, SEEK_SET);
    // д��Ҫ��������ݣ����ǣ�
    fwrite(data, 1, dataSize, file);
    // �ر��ļ�
    fclose(file);
}

unsigned char IsStringExisted(const char *filename,char initGameMark[],unsigned char LengthOfGameMark,unsigned int SearchOffset)
{
    FILE *file = fopen(filename, "rb");    
    if (file == NULL) 
    {
        printf("�޷����ļ�\n");
        printf("Can not open file.\n\n");
        return 0;
    }

    //��ʼĬ�ϲ�����
    unsigned char gIsStringExisted = false;
    char *gGameMark = (char *)malloc(LengthOfGameMark+1);// �����ڴ棬������һ�������ֽ������ַ���������
    if (gGameMark == NULL) 
    {
        printf("�ڴ����ʧ��\n");
        printf("Memory allocation failed\n\n");
        fclose(file);
        return 0; // ����һ��״̬�룬��ʾ�ڴ����ʧ��
    }

    fseek(file, SearchOffset, SEEK_SET);
    size_t bytesRead = fread(gGameMark, 1, LengthOfGameMark, file);
    gGameMark[LengthOfGameMark] = '\0'; // ����ַ���������

    if (bytesRead == LengthOfGameMark) 
    {
        for(int i = 0;i < LengthOfGameMark;i++)
        {
            if(gGameMark[i] != initGameMark[i])
            {    
                fclose(file);
                free(gGameMark);
                return gIsStringExisted;
            }
        }
        gIsStringExisted = true;
    }

    fclose(file);
    free(gGameMark);

    return gIsStringExisted;
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

void RangerCrypt(unsigned int *data, int size)
{
    int i;                 // r5
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

void CryptRanger1jp(const char *filename)
{
    FILE *sav = fopen(filename, "rb+");
    if (sav == NULL) {
        printf("�޷����ļ� \"%s\" ��\n�볢�������ļ��������������Ƴ��ļ����еĿո�\n\n", filename);
        printf("Can not open file \"%s\" .\nPlease try shortening the file name and removing spaces from the name.\n\n\n", filename);
        return;
    }

    //���浵��ʶ���Ƿ���Ѳ��Ա1��PKR-059 a00
    char gIsSaveExisted = true;
    char initGameMark[0xC] = {0x50,0x4B,0x52,0x2D,0x30,0x35,0x39,0x00,0x61,0x30,0x30,0x00}; //PKR-059 a00 
    gIsSaveExisted = IsStringExisted(filename,initGameMark,0xC,0);
    if(!gIsSaveExisted)
    {
        printf("���ļ����Ǳ�����Ѳ��Ա1���հ�Ĵ浵�����顣\n");
        printf("This file is not from pokemon ranger1 jp, please check.\n");
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
        RangerCrypt(DecryptedHeader, (R1JP_SAVE_HEADER_SIZE-0xC));
    
    //�ӽ����ļ�ͷ��������
    //��ͷ�������ļ�ͷ��������Ӧ������ȫһ�µľ��񱸷�
    for(int i = 0; i < 2;i++)
    {
        unsigned int *R1JPSaveheader = (unsigned int *)malloc((R1JP_SAVE_HEADER_SIZE-0xC));
        fseek(sav, 0xC + (R1JP_SAVE_HEADER_SIZE*i), SEEK_SET);
        fread(R1JPSaveheader, 1, (R1JP_SAVE_HEADER_SIZE-0xC), sav);
        if(!IsEncrypted)//����״̬������crc16
            R1JPSaveheader[1] = CRC16((char*)R1JPSaveheader+0x8, (R1JP_SAVE_HEADER_SIZE-0xC-0x8));
        RangerCrypt(R1JPSaveheader, (R1JP_SAVE_HEADER_SIZE-0xC));
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
                RangerCrypt(subchunk, (dataSize+0x18));
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

void DistributeRanger1jpMission(const char *filename)
{
    FILE *sav = fopen(filename, "rb+");
    if (sav == NULL) {
        printf("�޷����ļ� \"%s\" ��\n�볢�������ļ��������������Ƴ��ļ����еĿո�\n\n", filename);
        printf("Can not open file \"%s\" .\nPlease try shortening the file name and removing spaces from the name.\n\n\n", filename);
        return;
    }
    //��ȡ���ܵĴ浵ͷ���ݣ������浵��ʶ���������ں������������
    unsigned int *DecryptedHeader = (unsigned int *)malloc((R1JP_SAVE_HEADER_SIZE-0xC));
    fseek(sav, 0xC, SEEK_SET);
    fread(DecryptedHeader, 1, (R1JP_SAVE_HEADER_SIZE-0xC), sav);
    fclose(sav);
    //�������п������Լ��Ƿ���������ſ�
    int existedChunk = 0;
    enum {
        SISKIN,
        WREN,
        HAZEL,
        D001,
        D002,
        D003,
        D004
    };
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
            insertData(filename, SaveHeaderOfD00[i], 0x30, 0x20 + (existedChunk*0x30));
            insertData(filename, SaveHeaderOfD00[i], 0x30, 0x20 + (existedChunk*0x30) + 0x200);
            //д��siskin.tsd����brief
            insertData(filename, BriefOfD00[i], 0x56C, siskintsdChunkOffset + 0x30 + i*0x56C);
            insertData(filename, BriefOfD00[i], 0x56C, siskintsdChunkOffset + 0x30 + i*0x56C + 0x2700);
            //д����chunk
            insertData(filename, DataOfD00[i], ChunkSizeOfD00[i], NowChunkOffset);

            //����saveheader��chunkƫ�Ƶ�ַ
            FILE *sav = fopen(filename, "rb+");
            fseek(sav, (0x40 + (existedChunk*0x30)), SEEK_SET);
            fwrite(&NowChunkOffset, 1, 4, sav);
            //����siskin.tsd��new mission flag
            fseek(sav,siskintsdChunkOffset + 0x22,SEEK_SET);
            MissionNewFlag = fgetc(sav);
            MissionNewFlag = MissionNewFlag | (1<<i);
            fseek(sav,siskintsdChunkOffset + 0x22,SEEK_SET);
            fwrite(&MissionNewFlag, 1, 1, sav);
            unsigned int unknown = 0x01010101;
            fseek(sav,siskintsdChunkOffset + 0x18,SEEK_SET);
            fwrite(&unknown, 4, 1, sav);

            //����DecryptedHeader
            fseek(sav, 0xC, SEEK_SET);
            fread(DecryptedHeader, 1, (R1JP_SAVE_HEADER_SIZE-0xC), sav);
            fclose(sav);

            chunkOrder[i+3] = existedChunk;
            existedChunk++;
        }
    }
    free(DecryptedHeader);
    return;
}

void DistributeRanger23Mission(const char *filename,char initGameMark[],unsigned char LengthOfGameMark,unsigned int BaseOffset,unsigned int BlockSize,const unsigned char *const Mission[],unsigned char BlockSet[])
{
    char gIsMissionExisted = false;
    for(int i = 0; i < 6; i++)
    {   //����Ƿ��Ѿ���������
        gIsMissionExisted = IsStringExisted(filename,initGameMark,LengthOfGameMark,(BaseOffset + BlockSize * BlockSet[i]));
        //ע�뻹δ���յ�����
        if(!gIsMissionExisted)
            insertData(filename, Mission[i], BlockSize, (BaseOffset + BlockSize * BlockSet[i]));
    }
    return;
}
