#define TOOL_LANGUAGE_CHINESE_SIMPLIFIED    0
#define TOOL_LANGUAGE_ENGLISH               1
#define TOOL_LANGUAGE_COUNTS                2

#define TOOL_TEXTS_COUNTS                   74

const char *TextOfPRNMDTool[TOOL_LANGUAGE_COUNTS][TOOL_TEXTS_COUNTS] =
{
    [TOOL_LANGUAGE_CHINESE_SIMPLIFIED]=//GB2312字符集
    {
        [0]="请选择本工具显示语言，输入序号按回车键确定。 [1.中文 2.英文]\n",
        [1]="错误的参数，请重新选择。\n",
        [2]="警告：您并没有提供需要配信的存档文件。请将存档拖至本程序上或在命令行内以如下方式输入存档名。\n"
            "用法: PRNMDTool.exe [文件1] [文件2] ...\n\n",
        [3]="按下回车键退出程序...\n",
        [4]="%d 个文件将被处理。\n\n",
        [5]="*---------------第 %d 个文件处理中---------------*\n",
        [6]="文件名： \"%s\" \n\n",
        [7]="已配信_",
        [8]="请检查文件名，无法打开文件 \"%s\"。\n",
        [9]="第 %d 个文件处理结束。\n\n",
        [10]="请检查文件名，无法创建另存文件 \"%s\"。\n",
        [11]="警告：错误的巡护员1存档。\n",
        [12]="警告：错误的存档，或不包含游戏进度的巡护员1、2、3存档，工具无法识别。\n",
        [13]="存档版本：巡护员 %d 代。\n",
        [14]="存档版本(及语言)：巡护员 %d 代(日版)。\n",
        [15]="存档版本(及语言)：巡护员 %d 代(海外版)。\n",
        [16]="存档版本(及语言)：巡护员 %d 代(北美英语版)。\n",
        [17]="存档版本(及语言)：巡护员 %d 代(欧洲英语版)。\n",
        [18]="存档版本(及语言)：巡护员 %d 代(欧洲法语版)。\n",
        [19]="存档版本(及语言)：巡护员 %d 代(欧洲意大利语版)。\n",
        [20]="存档版本(及语言)：巡护员 %d 代(欧洲德语版)。\n",
        [21]="存档版本(及语言)：巡护员 %d 代(欧洲西班牙语版)。\n",
        [22]="\n此文件无需进行重复配信。\n",
        [23]="\n详见文件： \"%s\" \n",
        [24]="*============ %d 个文件已全部处理完成============*\n\n",
        [25]="*** 注意：本次处理的文件中包含巡护员1代海外版，无需配信，任务开启方式详见上文说明。\n\n",
        [26]="无法打开文件。\n\n",
        [27]="配信完成！任务D001：夺回珍贵的蛋！\n",
        [28]="配信完成！任务D002：取得代欧奇希斯的信任？！\n",
        [29]="配信完成！任务D003：营救时拉比！\n",
        [30]="配信完成！任务D004：寻找幻之梦幻！\n",
        [31]="无需配信！已接收过 任务D001：夺回珍贵的蛋！\n",
        [32]="无需配信！已接收过 任务D002：取得代欧奇希斯的信任？！\n",
        [33]="无需配信！已接收过 任务D003：营救时拉比！\n",
        [34]="无需配信！已接收过 任务D004：寻找幻之梦幻！\n",
        [35]="注：巡护员1代海外版无需通过配信获取任务。\n"
             "　　一周目通关后将自动开启3个任务，需依次完成上一个任务后才能开启下一个任务。\n"
             "　　一周目通关后在巡护员网络界面按下“R+X+LEFT”可激活输入密码选项。\n\n"
             "　　在密码界面输入以下密码可开启玛纳霏任务：\n"
             "　　*北美版　　　　：P8M2-9D6F-43H7\n"
             "　　*欧洲英文版　　：Mg35-Cpb8-4FW8\n"
             "　　*欧洲法文版　　：DY4g-k28S-QB9F\n"
             "　　*欧洲德文版　　：R3d4-cv2S-WC7W\n"
             "　　*欧洲西班牙文版：C58f-t3WT-Vn79\n"
             "　　*欧洲意大利文版：FH38-fwD8-5S2a\n"
             "\n",
        [36]="配信完成！特殊任务1：取得玛纳霏的蛋！\n",
        [37]="配信完成！特殊任务2：营救被绑架的利欧路！\n",
        [38]="配信完成！特殊任务3：保卫大家的塔吧！\n",
        [39]="配信完成！附加任务1：冷水谷的帝牙卢卡！？\n",
        [40]="配信完成！附加任务2：渺远沙漠的帕路奇亚！？\n",
        [41]="配信完成！附加任务3：为了花之新娘与谢米！\n",
        [42]="无需配信！已接收过 特殊任务1：取得玛纳霏的蛋！\n",
        [43]="无需配信！已接收过 特殊任务2：营救被绑架的利欧路！\n",
        [44]="无需配信！已接收过 特殊任务3：保卫大家的塔吧！\n",
        [45]="无需配信！已接收过 附加任务1：冷水谷的帝牙卢卡！？\n",
        [46]="无需配信！已接收过 附加任务2：渺远沙漠的帕路奇亚！？\n",
        [47]="无需配信！已接收过 附加任务3：为了花之新娘与谢米！\n",
        [48]="配信完成！特殊任务1：守护传说中的蓝色圆球！\n",
        [49]="配信完成！特殊任务2：调查神秘的火山爆发！\n",
        [50]="配信完成！特殊任务3：保护迷路的谢米！\n",
        [51]="配信完成！追加任务1：寻找骑拉帝纳的白金宝珠！\n",
        [52]="配信完成！追加任务2：向阿尔宙斯承诺！\n",
        [53]="配信完成！特殊任务4：代欧奇希斯与谜之神殿\n",
        [54]="无需配信！已接收过 特殊任务1：守护传说中的蓝色圆球！\n",
        [55]="无需配信！已接收过 特殊任务2：调查神秘的火山爆发！\n",
        [56]="无需配信！已接收过 特殊任务3：保护迷路的谢米！\n",
        [57]="无需配信！已接收过 追加任务1：寻找骑拉帝纳的白金宝珠！\n",
        [58]="无需配信！已接收过 追加任务2：向阿尔宙斯承诺！\n",
        [59]="无需配信！已接收过 特殊任务4：代欧奇希斯与谜之神殿\n",
        [60]="或你是否需要创建一个包含配信数据的初始存档？输入序号按回车键确定。 [1.是 2.否]\n：",
        [61]="\n您想创建的初始配信存档的版本是？输入序号按回车键确定。 \n[1.巡护员1-日版 2.巡护员2风涌篇-日版&海外版通用 3.巡护员3光之轨迹-日版 4.巡护员3光之轨迹-海外版]\n：",
        [62]="初始配信存档_巡护员1代_日版.sav",
        [63]="初始配信存档_巡护员2代_日版&海外版通用.sav",
        [64]="初始配信存档_巡护员3代_日版.sav",
        [65]="初始配信存档_巡护员3代_海外版.sav",
        [66]="无法创建文件。\n",
        [67]="\n初始配信存档已创建，详见文件： \"%s\" \n",
        [68]="\n是否继续创建其他初始配信存档？输入序号按回车键确定。 [1.是 2.否]\n：",
        [69]="\n检测到该巡护员1存档玛娜霏任务已接收蛋，还未传送至其他作品，是否需要将任务重置为未接收蛋的状态？输入序号按回车键确定。 [1.是 2.否]\n：",
        [70]="\n检测到该巡护员1存档玛娜霏任务已传送至其他作品，是否需要将任务重置为未接收蛋的状态，或已接收蛋但未传送至其他作品的状态？输入序号按回车键确定。\n[1.重置为未接收蛋的状态 2.重置为已接收蛋但未传送至其他作品的状态 3.否]\n：",
        [71]="\n已将该巡护员1存档的玛娜霏任务重置为未接收蛋的状态。\n",
        [72]="\n已将该巡护员1存档的玛娜霏任务重置为已接收蛋但未传送至其他作品的状态。\n",
        [73]="\n注：您需要在通关情况下才可进行玛娜霏任务的相关操作。\n"
    },

    [TOOL_LANGUAGE_ENGLISH]=
    {
        [0]="Please select the display language of this tool, enter the serial number and press Enter to confirm. [1. Chinese 2. English]\n",
        [1]="Wrong parameters, please select again.\n",
        [2]="Warning: You didn't provide sav file(s) that needs distribution. Please drag save file(s) onto this program or enter save filename(s) in the command line as follows.\n"
            "Usage: PRNMDTool.exe [file1] [file2] ...\n\n",
        [3]="Press Enter to exit...\n",
        [4]="%d File(s) will be processed.\n\n",
        [5]="*---------------File %d is being processed---------------*\n",
        [6]="FileName: \"%s\" \n\n",
        [7]="Distributed_",
        [8]="Please check your file name. Can not open file \"%s\".\n",
        [9]="File %d was processed.\n\n",
        [10]="Please check your file name. Can not create new file \"%s\".\n",
        [11]="Warning: This is a wrong savefile of ranger1.\n",
        [12]="Warning: Wrong savefile or ranger 1, 2, 3 savefile that do not contain game progress. It can't be read by tool.\n",
        [13]="Save Version: Ranger %d .\n",
        [14]="Save Version (& Language): Ranger %d (jp).\n",
        [15]="Save Version (& Language): Ranger %d (oversea).\n",
        [16]="Save Version (& Language): Ranger %d (us-en).\n",
        [17]="Save Version (& Language): Ranger %d (eu-en).\n",
        [18]="Save Version (& Language): Ranger %d (eu-fr).\n",
        [19]="Save Version (& Language): Ranger %d (eu-it).\n",
        [20]="Save Version (& Language): Ranger %d (eu-de).\n",
        [21]="Save Version (& Language): Ranger %d (eu-sp).\n",
        [22]="\nThis file does not need to be distributed again.\n",
        [23]="\nSee File: \"%s\" \n",
        [24]="*============ %d File(s) are all done============*\n\n",
        [25]="*** Note: Ranger1 Oversea file existed, which don't need to be distributed. See above to know how to unlock mission on Ranger1 oversea.\n\n",
        [26]="Can not open file.\n\n",
        [27]="Distributed! MissionD001: Recover the Precious Egg!\n",
        [28]="Distributed! MissionD002: Gain Deoxys's Trust?!\n",
        [29]="Distributed! MissionD003: Rescue Celebi!\n",
        [30]="Distributed! MissionD004: Find Mew, the Mirage!\n",
        [31]="NoNeed ToDo! Already Gotten MissionD001: Recover the Precious Egg!!\n",
        [32]="NoNeed ToDo! Already Gotten MissionD002: Gain Deoxys's Trust?!!\n",
        [33]="NoNeed ToDo! Already Gotten MissionD003: Rescue Celebi!!\n",
        [34]="NoNeed ToDo! Already Gotten MissionD004: Find Mew, the Mirage!!\n",
        [35]="Note: Ranger1 oversea don't need to be distributed.\n"
             "      After finishing the first game, Ranger Net will auto boot 3 missions, which you should finish the previous mission to unlock the next mission.\n"
             "      After finishing the first game, holding R+X+Left on the Ranger Net screen can unlock \"Enter the password\" option.\n\n"
             "      Then enter the code followed to unlock the Manaphy mission:\n"
             "      *US-en: P8M2-9D6F-43H7\n"
             "      *EU-en: Mg35-Cpb8-4FW8\n"
             "      *EU-fr: DY4g-k28S-QB9F\n"
             "      *EU-de: R3d4-cv2S-WC7W\n"
             "      *EU-sp: C58f-t3WT-Vn79\n"
             "      *EU-it: FH38-fwD8-5S2a\n"
             "\n",
        [36]="Distributed! SpecialMission1: Recover the Manaphy Egg!\n",
        [37]="Distributed! SpecialMission2: Rescue Kidnapped Riolu!\n",
        [38]="Distributed! SpecialMission3: Liberate the Tower!\n",
        [39]="Distributed! ExtraMission1: Dialga in Hia Valley!?\n",
        [40]="Distributed! ExtraMission2: Palkia in Haruba Desert!?\n",
        [41]="Distributed! ExtraMission3: For the Bride and Shaymin!\n",
        [42]="NoNeed ToDo! Already Gotten SpecialMission1: Recover the Manaphy Egg!!\n",
        [43]="NoNeed ToDo! Already Gotten SpecialMission2: Rescue Kidnapped Riolu!!\n",
        [44]="NoNeed ToDo! Already Gotten SpecialMission3: Liberate the Tower!!\n",
        [45]="NoNeed ToDo! Already Gotten ExtraMission1: Dialga in Hia Valley!?!\n",
        [46]="NoNeed ToDo! Already Gotten ExtraMission2: Palkia in Haruba Desert!?!\n",
        [47]="NoNeed ToDo! Already Gotten ExtraMission3: For the Bride and Shaymin!!\n",
        [48]="Distributed! SpecialMission1: Protect The Blue Sphere!\n",
        [49]="Distributed! SpecialMission2: Investigate the Odd Eruption!!\n",
        [50]="Distributed! SpecialMission3: Rescue the Lost Shaymin!!\n",
        [51]="Distributed! ExtraMission1: Find Giratina's Griseous Orb!!\n",
        [52]="Distributed! ExtraMission2: Pledge to Arceus!\n",
        [53]="Distributed! SpecialMission4: Deoxys and the Odd Temple!\n",
        [54]="NoNeed ToDo! Already Gotten SpecialMission1: Protect The Blue Sphere!\n",
        [55]="NoNeed ToDo! Already Gotten SpecialMission2: Investigate the Odd Eruption!!\n",
        [56]="NoNeed ToDo! Already Gotten SpecialMission3: Rescue the Lost Shaymin!!\n",
        [57]="NoNeed ToDo! Already Gotten ExtraMission1: Find Giratina's Griseous Orb!!\n",
        [58]="NoNeed ToDo! Already Gotten ExtraMission2: Pledge to Arceus!\n",
        [59]="NoNeed ToDo! Already Gotten SpecialMission4: Deoxys and the Odd Temple!\n",
        [60]="Or do you need to create an initial sav file containing distribution data? Enter the serial number and press Enter to confirm. [1.Yes 2.No]\n:",
        [61]="\nWhat initial distribution sav do you want to create? Enter the serial number and press Enter to confirm.\n[1.Ranger1(jp) 2.Raner2_Shadows_of_Almia(jp&oversea) 3.Ranger3_Guardian_Signs(jp) 4.Ranger3_Guardian_Signs(oversea)]\n:",
        [62]="InitialDistributinoSave_Ranger1_jp.sav",
        [63]="InitialDistributinoSave_Ranger2_Shadows_of_Almia_jp&oversea.sav",
        [64]="InitialDistributinoSave_Ranger3_Guardian_Signs_jp.sav",
        [65]="InitialDistributinoSave_Ranger3_Guardian_Signs_oversea.sav",
        [66]="Can not creat file.\n",
        [67]="\nInitial distribution sav has been made, see file:  \"%s\" \n",
        [68]="\nDo you want to continue creating additional initial distribution save(s)? Enter the serial number and press Enter to confirm. [1.Yes 2.No]\n:",
        [69]="\nIt's detected that this Ranger1 Manaphy mission has received eggs, but hasn't been transferred to DPPtHGSS.\nDo you need to reset the mission to the state where the egg hasn't been received?\nEnter the serial number and press Enter to confirm. [1.Yes 2.No]\n:",
        [70]="\nIt's detected that this Ranger1 Manaphy mission has transferred Manaphy Egg to DPPtHGSS.\nDo you need to reset the mission to the state where the egg hasn't been received,\nor the state where the egg has been received but not transferred to DPPtHGSS?\nEnter the serial number and press Enter to confirm.\n[1.Reset to the state where the egg hasn't been received\n 2.Reset to the state where the egg has been received but not sent to DPPtHGSS.\n 3.No]\n:",
        [71]="\nThe Manaphy mission of this Ranger1 sav has been reset to the state where the egg hasn't been received.\n",
        [72]="\nThe Manaphy mission of this Ranger1 sav has been reset to the state where the egg has been received but not sent to DPPtHGSS.\n",
        [73]="\nNote: You need to finish game before you can perform operations related to the Manaphy mission.\n"
    },
};