//"********************CCDC01²É¼¯Æ÷²âÊÔÒÇÈí¼ş£ºÆ´ÒôÊäÈë·¨Ä£¿é********************"
//"*                              Èí¼şÉè¼Æ£ºÕÅ ¿­                               *"
//"*                             ÈÕÆÚ£º    2001/3                               *"
//"*                         ±àÒë»·¾³£ºFranklin 3.3.4                           *"
//"******************************************************************************"

#include <string.h>
#include <reg51.h>

//"********************CCDC01²É¼¯Æ÷²âÊÔÒÇÈí¼ş£ºÆ´ÒôÊäÈë·¨Âë±í********************"
//"*                              Èí¼şÉè¼Æ£ºÕÅ ¿­                               *"
//"*                             ÈÕÆÚ£º    2001/3                               *"
//"*                         ±àÒë»·¾³£ºFranklin 3.3.4                           *"
//"******************************************************************************"

//"Æ´ÒôÊäÈë·¨ºº×ÖÅÅÁĞ±í"
unsigned char code PY_mb_a     []={"°¢°¡"};
unsigned char code PY_mb_ai    []={"°¥°§°¦°£°¤°¨°©°«°ª°¬°®°¯°­"};
unsigned char code PY_mb_an    []={"°²°±°°°³°¶°´°¸°·°µ"};
unsigned char code PY_mb_ang   []={"°¹°º°»"};
unsigned char code PY_mb_ao    []={"°¼°½°¾°¿°À°Á°Â°Ä°Ã"};
unsigned char code PY_mb_ba    []={"°Ë°Í°È°Ç°É°Å°Ì°Æ°Ê°Î°Ï°Ñ°Ğ°Ó°Ö°Õ°Ô"};
unsigned char code PY_mb_bai   []={"°×°Ù°Û°Ø°Ú°Ü°İ°Ş"};
unsigned char code PY_mb_ban   []={"°â°à°ã°ä°ß°á°å°æ°ì°ë°é°ç°è°í°ê"};
unsigned char code PY_mb_bang  []={"°î°ï°ğ°ó°ñ°ò°ö°ø°ô°ù°õ°÷"};
unsigned char code PY_mb_bao   []={"°ü°ú°û°ı±¢±¦±¥±£±¤±¨±§±ª±«±©±¬°ş±¡ÆÙ"};
unsigned char code PY_mb_bei   []={"±°±­±¯±®±±±´±·±¸±³±µ±¶±»±¹±º±²"};
unsigned char code PY_mb_ben   []={"±¼±¾±½±¿º»"};
unsigned char code PY_mb_beng  []={"±À±Á±Â±Ã±Å±Ä"};
unsigned char code PY_mb_bi    []={"±Æ±Ç±È±Ë±Ê±É±Ò±Ø±Ï±Õ±Ó±Ñ±İ±Ğ±Ö±Ô±Í±×±Ì±Î±Ú±Ü±Û"};
unsigned char code PY_mb_bian  []={"±ß±à±Ş±á±â±å±ã±ä±é±æ±ç±è"};
unsigned char code PY_mb_biao  []={"±ë±ê±ì±í"};
unsigned char code PY_mb_bie   []={"±ï±î±ğ±ñ"};
unsigned char code PY_mb_bin   []={"±ö±ò±ó±õ±ô±÷"};
unsigned char code PY_mb_bing  []={"±ù±ø±û±ü±ú±ş±ı²¢²¡"};
unsigned char code PY_mb_bo    []={"²¦²¨²£²§²±²¤²¥²®²µ²¯²´²ª²¬²°²©²³²«²­²²²·"};
unsigned char code PY_mb_bu    []={"²¹²¸²¶²»²¼²½²À²¿²º²¾"};
unsigned char code PY_mb_ca    []={"²Á"};
unsigned char code PY_mb_cai   []={"²Â²Å²Ä²Æ²Ã²É²Ê²Ç²È²Ë²Ì"};
unsigned char code PY_mb_can   []={"²Î²Í²Ğ²Ï²Ñ²Ò²Ó"};
unsigned char code PY_mb_cang  []={"²Ö²×²Ô²Õ²Ø"};
unsigned char code PY_mb_cao   []={"²Ù²Ú²Ü²Û²İ"};
unsigned char code PY_mb_ce    []={"²á²à²Ş²â²ß"};
unsigned char code PY_mb_ceng  []={"²ã²äÔø"};
unsigned char code PY_mb_cha   []={"²æ²å²é²ç²è²ë²ì²ê²í²ï²îÉ²"};
unsigned char code PY_mb_chai  []={"²ğ²ñ²ò"};
unsigned char code PY_mb_chan  []={"²ô²ó²÷²ö²ø²õ²ú²ù²û²ü"};
unsigned char code PY_mb_chang []={"²ı²ş³¦³¢³¥³£³§³¡³¨³©³«³ª"};
unsigned char code PY_mb_chao  []={"³­³®³¬³²³¯³°³±³³³´´Â"};
unsigned char code PY_mb_che   []={"³µ³¶³¹³¸³·³º"};
unsigned char code PY_mb_chen  []={"³»³¾³¼³À³Á³½³Â³¿³Ä³Ã"};
unsigned char code PY_mb_cheng []={"³Æ³Å³É³Ê³Ğ³Ï³Ç³Ë³Í³Ì³Î³È³Ñ³Ò³Ó"};
unsigned char code PY_mb_chi   []={"³Ô³Õ³Ú³Ø³Û³Ù³Ö³ß³Ş³İ³Ü³â³à³ã³á"};
unsigned char code PY_mb_chong []={"³ä³å³æ³ç³è"};
unsigned char code PY_mb_chou  []={"³é³ğ³ñ³ë³î³í³ï³ê³ì³ó³ò³ô"};
unsigned char code PY_mb_chu   []={"³ö³õ³ı³ø³ü³ú³û³÷³ù´¡´¢³ş´¦´¤´¥´£Ğó"};
unsigned char code PY_mb_chuai []={"´§"};
unsigned char code PY_mb_chuan []={"´¨´©´«´¬´ª´­´®"};
unsigned char code PY_mb_chuang[]={"´³´¯´°´²´´"};
unsigned char code PY_mb_chui  []={"´µ´¶´¹´·´¸"};
unsigned char code PY_mb_chun  []={"´º´»´¿´½´¾´¼´À"};
unsigned char code PY_mb_chuo  []={"´Á"};
unsigned char code PY_mb_ci    []={"´Ã´Ê´Ä´É´È´Ç´Å´Æ´Ë´Î´Ì´Í"};
unsigned char code PY_mb_cong  []={"´Ñ´Ó´Ò´Ğ´Ï´Ô"};
unsigned char code PY_mb_cou   []={"´Õ"};
unsigned char code PY_mb_cu    []={"´Ö´Ù´×´Ø"};
unsigned char code PY_mb_cuan  []={"´Ú´Ü´Û"};
unsigned char code PY_mb_cui   []={"´Ş´ß´İ´à´ã´á´â´ä"};
unsigned char code PY_mb_cun   []={"´å´æ´ç"};
unsigned char code PY_mb_cuo   []={"´ê´è´é´ì´ë´í"};
unsigned char code PY_mb_da    []={"´î´ï´ğ´ñ´ò´ó"};
unsigned char code PY_mb_dai   []={"´ô´õ´ö´ú´ø´ıµ¡´ù´û´ü´ş´÷"};
unsigned char code PY_mb_dan   []={"µ¤µ¥µ£µ¢µ¦µ¨µ§µ©µ«µ®µ¯µ¬µ­µ°µª"};
unsigned char code PY_mb_dang  []={"µ±µ²µ³µ´µµ"};
unsigned char code PY_mb_dao   []={"µ¶µ¼µºµ¹µ·µ»µ¸µ½µ¿µÁµÀµ¾"};
unsigned char code PY_mb_de    []={"µÃµÂµÄ"};
unsigned char code PY_mb_deng  []={"µÆµÇµÅµÈµËµÊµÉ"};
unsigned char code PY_mb_di    []={"µÍµÌµÎµÒµÏµĞµÓµÑµÕµ×µÖµØµÜµÛµİµÚµŞµÙ"};
unsigned char code PY_mb_dian  []={"µàµáµßµäµãµâµçµèµéµêµæµëµíµìµîµå"};
unsigned char code PY_mb_diao  []={"µóµğµòµïµñµõµöµô"};
unsigned char code PY_mb_die   []={"µùµøµüµıµşµúµû"};
unsigned char code PY_mb_ding  []={"¶¡¶£¶¢¶¤¶¥¶¦¶©¶¨¶§"};
unsigned char code PY_mb_diu   []={"¶ª"};
unsigned char code PY_mb_dong  []={"¶«¶¬¶­¶®¶¯¶³¶±¶²¶°¶´"};
unsigned char code PY_mb_dou   []={"¶¼¶µ¶·¶¶¶¸¶¹¶º¶»"};
unsigned char code PY_mb_du    []={"¶½¶¾¶Á¶¿¶À¶Â¶Ä¶Ã¶Ê¶Å¶Ç¶È¶É¶Æ"};
unsigned char code PY_mb_duan  []={"¶Ë¶Ì¶Î¶Ï¶Ğ¶Í"};
unsigned char code PY_mb_dui   []={"¶Ñ¶Ó¶Ô¶Ò"};
unsigned char code PY_mb_dun   []={"¶Ö¶Ø¶Õ¶×¶Ü¶Û¶Ù¶İ"};
unsigned char code PY_mb_duo   []={"¶à¶ß¶á¶Ş¶ä¶â¶ã¶ç¶é¶æ¶è¶å"};
unsigned char code PY_mb_e     []={"¶ï¶í¶ğ¶ë¶ì¶ê¶î¶ò¶ó¶ñ¶ö¶õ¶ô"};
unsigned char code PY_mb_en    []={"¶÷"};
unsigned char code PY_mb_er    []={"¶ù¶ø¶û¶ú¶ı¶ü¶ş·¡"};
unsigned char code PY_mb_fa    []={"·¢·¦·¥·£·§·¤·¨·©"};
unsigned char code PY_mb_fan   []={"·«·¬·­·ª·²·¯·°·³·®·±·´·µ·¸·º·¹·¶··"};
unsigned char code PY_mb_fang  []={"·½·»·¼·À·Á·¿·¾·Â·Ã·Ä·Å"};
unsigned char code PY_mb_fei   []={"·É·Ç·È·Æ·Ê·Ë·Ì·Í·Ï·Ğ·Î·Ñ"};
unsigned char code PY_mb_fen   []={"·Ö·Ô·×·Ò·Õ·Ó·Ø·Ú·Ù·Û·İ·Ü·Ş·ß·à"};
unsigned char code PY_mb_feng  []={"·á·ç·ã·â·è·å·é·æ·ä·ë·ê·ì·í·ï·î"};
unsigned char code PY_mb_fo    []={"·ğ"};
unsigned char code PY_mb_fou   []={"·ñ"};
unsigned char code PY_mb_fu    []={"·ò·ô·õ·ó¸¥·ü·ö·÷·ş·ı·ú¸¡¸¢·û¸¤·ù¸£·ø¸§¸¦¸®¸«¸©¸ª¸¨¸­¸¯¸¸¸¼¸¶¸¾¸º¸½¸À¸·¸´¸°¸±¸µ¸»¸³¸¿¸¹¸²"};
unsigned char code PY_mb_ga    []={"¸Â¸Á"};
unsigned char code PY_mb_gai   []={"¸Ã¸Ä¸Æ¸Ç¸È¸Å"};
unsigned char code PY_mb_gan   []={"¸É¸Ê¸Ë¸Î¸Ì¸Í¸Ñ¸Ï¸Ò¸Ğ¸Ó"};
unsigned char code PY_mb_gang  []={"¸Ô¸Õ¸Ú¸Ù¸Ø¸×¸Ö¸Û¸Ü"};
unsigned char code PY_mb_gao   []={"¸Ş¸á¸ß¸à¸İ¸â¸ã¸å¸ä¸æ"};
unsigned char code PY_mb_ge    []={"¸ê¸í¸ç¸ì¸ë¸î¸é¸è¸ó¸ï¸ñ¸ğ¸ô¸ö¸÷¸õ¿©"};
unsigned char code PY_mb_gei   []={"¸ø"};
unsigned char code PY_mb_gen   []={"¸ù¸ú"};
unsigned char code PY_mb_geng  []={"¸ü¸ı¸û¸ş¹¡¹¢¹£"};
unsigned char code PY_mb_gong  []={"¹¤¹­¹«¹¦¹¥¹©¹¬¹§¹ª¹¨¹®¹¯¹°¹²¹±"};
unsigned char code PY_mb_gou   []={"¹´¹µ¹³¹·¹¶¹¹¹º¹¸¹»"};
unsigned char code PY_mb_gu    []={"¹À¹¾¹Ã¹Â¹Á¹½¹¼¹¿¹Å¹È¹É¹Ç¹Æ¹Ä¹Ì¹Ê¹Ë¹Í"};
unsigned char code PY_mb_gua   []={"¹Ï¹Î¹Ğ¹Ñ¹Ò¹Ó"};
unsigned char code PY_mb_guai  []={"¹Ô¹Õ¹Ö"};
unsigned char code PY_mb_guan  []={"¹Ø¹Û¹Ù¹Ú¹×¹İ¹Ü¹á¹ß¹à¹Ş"};
unsigned char code PY_mb_guang []={"¹â¹ã¹ä"};
unsigned char code PY_mb_gui   []={"¹é¹ç¹ê¹æ¹ë¹è¹å¹ì¹î¹ï¹í¹ô¹ñ¹ó¹ğ¹ò"};
unsigned char code PY_mb_gun   []={"¹õ¹ö¹÷"};
unsigned char code PY_mb_guo   []={"¹ù¹ø¹ú¹û¹ü¹ı"};
unsigned char code PY_mb_ha    []={"¸ò¹ş"};
unsigned char code PY_mb_hai   []={"º¢º¡º£º¥º§º¦º¤"};
unsigned char code PY_mb_han   []={"º¨º©º¬ºªº¯º­º®º«º±º°ººº¹ºµº·º´º¸º¶º³º²"};
unsigned char code PY_mb_hang  []={"º¼º½ĞĞ"};
unsigned char code PY_mb_hao   []={"ºÁºÀº¿º¾ºÃºÂºÅºÆºÄ"};
unsigned char code PY_mb_he    []={"ºÇºÈºÌºÏºÎºÍºÓºÒºËºÉºÔºĞºÊºØºÖºÕº×"};
unsigned char code PY_mb_hei   []={"ºÚºÙ"};
unsigned char code PY_mb_hen   []={"ºÛºÜºİºŞ"};
unsigned char code PY_mb_heng  []={"ºàºßºãºáºâ"};
unsigned char code PY_mb_hong  []={"ºäºåºæºëºìºêºéºçºè"};
unsigned char code PY_mb_hou   []={"ºîºíºïºğºóºñºò"};
unsigned char code PY_mb_hu    []={"ºõºôºö»¡ºüºúºøºşºùº÷ºıºû»¢»£»¥»§»¤»¦"};
unsigned char code PY_mb_hua   []={"»¨»ª»©»¬»«»¯»®»­»°"};
unsigned char code PY_mb_huai  []={"»³»²»´»±»µ"};
unsigned char code PY_mb_huan  []={"»¶»¹»·»¸»º»Ã»Â»½»»»Á»¼»À»¾»¿"};
unsigned char code PY_mb_huang []={"»Ä»Å»Ê»Ë»Æ»Ì»Í»È»Ç»É»Ğ»Î»Ñ»Ï"};
unsigned char code PY_mb_hui   []={"»Ò»Ö»Ó»Ô»Õ»Ø»×»Ú»Ü»ã»á»ä»æ»å»â»ß»Ş»à»İ»Ù»Û"};
unsigned char code PY_mb_hun   []={"»è»ç»é»ë»ê»ì"};
unsigned char code PY_mb_huo   []={"»í»î»ğ»ï»ò»õ»ñ»ö»ó»ô"};
unsigned char code PY_mb_ji    []={"¼¥»÷¼¢»ø»ú¼¡¼¦¼£¼§»ı»ù¼¨¼©»û»ş»ü¼¤¼°¼ª¼³¼¶¼´¼«¼±¼²¼¬¼¯¼µ¼­¼®¼¸¼º¼·¼¹¼Æ¼Ç¼¿¼Í¼Ë¼É¼¼¼Ê¼Á¼¾¼È¼Ã¼Ì¼Å¼Ä¼Â¼À¼»¼½½å"};
unsigned char code PY_mb_jia   []={"¼Ó¼Ğ¼Ñ¼Ï¼Ò¼Î¼Ô¼Õ¼×¼Ö¼Ø¼Û¼İ¼Ü¼Ù¼Ş¼ÚĞ®"};
unsigned char code PY_mb_jian  []={"¼é¼â¼á¼ß¼ä¼ç¼è¼æ¼à¼ã¼ê¼å¼ğ¼ó¼í¼ë¼ñ¼õ¼ô¼ì¼ï¼ò¼î¼û¼ş½¨½¤½£¼ö¼ú½¡½§½¢½¥½¦¼ù¼ø¼ü¼ı"};
unsigned char code PY_mb_jiang []={"½­½ª½«½¬½©½®½²½±½°½¯½³½µ½´"};
unsigned char code PY_mb_jiao  []={"½»½¼½¿½½½¾½º½·½¹½¶½¸½Ç½Æ½Ê½È½Ã½Å½Â½Á½Ë½É½Ğ½Î½Ï½Ì½Ñ½Í¾õ½À"};
unsigned char code PY_mb_jie   []={"½×½Ô½Ó½Õ½Ò½Ö½Ú½Ù½Ü½à½á½İ½Ş½Ø½ß½ã½â½é½ä½æ½ì½ç½ê½ë½è"};
unsigned char code PY_mb_jin   []={"½í½ñ½ï½ğ½ò½î½ó½ö½ô½÷½õ¾¡¾¢½ü½ø½ú½ş½ı½û½ù"};
unsigned char code PY_mb_jing  []={"¾©¾­¾¥¾£¾ª¾§¾¦¾¬¾¤¾«¾¨¾®¾±¾°¾¯¾»¾¶¾·¾º¾¹¾´¾¸¾³¾²¾µ"};
unsigned char code PY_mb_jiong []={"¾¼¾½"};
unsigned char code PY_mb_jiu   []={"¾À¾¿¾¾¾Å¾Ã¾Ä¾Á¾Â¾Æ¾É¾Ê¾Ì¾Î¾Ç¾È¾Í¾Ë"};
unsigned char code PY_mb_ju    []={"¾Ó¾Ğ¾Ñ¾Ô¾Ò¾Ï¾Ö½Û¾Õ¾×¾Ú¾Ù¾Ø¾ä¾Ş¾Ü¾ß¾æ¾ã¾ç¾å¾İ¾à¾â¾Û¾á"};
unsigned char code PY_mb_juan  []={"¾ê¾è¾é¾í¾ë¾î¾ì"};
unsigned char code PY_mb_jue   []={"¾ï¾ö¾÷¾ñ¾ø¾ó¾ò¾ô¾ğ"};
unsigned char code PY_mb_jun   []={"¾ü¾ı¾ù¾û¾ú¿¡¿¤¾ş¿£¿¥¿¢"};
unsigned char code PY_mb_ka    []={"¿§¿¦¿¨"};
unsigned char code PY_mb_kai   []={"¿ª¿«¿­¿®¿¬"};
unsigned char code PY_mb_kan   []={"¼÷¿¯¿±¿°¿²¿³¿´"};
unsigned char code PY_mb_kang  []={"¿µ¿¶¿·¿¸¿º¿¹¿»"};
unsigned char code PY_mb_kao   []={"¿¼¿½¿¾¿¿"};
unsigned char code PY_mb_ke    []={"¿À¿Á¿Â¿Æ¿Ã¿Å¿Ä¿Ç¿È¿É¿Ê¿Ë¿Ì¿Í¿Î"};
unsigned char code PY_mb_ken   []={"¿Ï¿Ñ¿Ò¿Ğ"};
unsigned char code PY_mb_keng  []={"¿Ô¿Ó"};
unsigned char code PY_mb_kong  []={"¿Õ¿×¿Ö¿Ø"};
unsigned char code PY_mb_kou   []={"¿Ù¿Ú¿Û¿Ü"};
unsigned char code PY_mb_ku    []={"¿İ¿Ş¿ß¿à¿â¿ã¿á"};
unsigned char code PY_mb_kua   []={"¿ä¿å¿æ¿è¿ç"};
unsigned char code PY_mb_kuai  []={"¿é¿ì¿ë¿ê"};
unsigned char code PY_mb_kuan  []={"¿í¿î"};
unsigned char code PY_mb_kuang []={"¿ï¿ğ¿ñ¿ö¿õ¿ó¿ò¿ô"};
unsigned char code PY_mb_kui   []={"¿÷¿ù¿ø¿ú¿ü¿û¿ı¿şÀ¢À£À¡"};
unsigned char code PY_mb_kun   []={"À¤À¥À¦À§"};
unsigned char code PY_mb_kuo   []={"À©À¨À«Àª"};
unsigned char code PY_mb_la    []={"À¬À­À²À®À°À¯À±"};
unsigned char code PY_mb_lai   []={"À´À³Àµ"};
unsigned char code PY_mb_lan   []={"À¼À¹À¸À·À»À¶À¾À½ÀºÀÀÀ¿ÀÂÀÁÀÃÀÄ"};
unsigned char code PY_mb_lang  []={"ÀÉÀÇÀÈÀÅÀÆÀÊÀË"};
unsigned char code PY_mb_lao   []={"ÀÌÀÍÀÎÀÏÀĞÀÑÀÔÀÓÀÒ"};
unsigned char code PY_mb_le    []={"ÀÖÀÕÁË"};
unsigned char code PY_mb_lei   []={"À×ÀØÀİÀÚÀÙÀÜÀßÀáÀàÀÛÀŞ"};
unsigned char code PY_mb_leng  []={"ÀâÀãÀä"};
unsigned char code PY_mb_li    []={"ÀåÀæÀêÀëÀòÀçÀìÁ§ÀèÀéÀñÀîÀïÁ¨ÀíÀğÁ¦ÀúÀ÷Á¢ÀôÀöÀûÀøÁ¤ÀıÁ¥ÀşÀóÀõÀùÁ£ÀüÁ¡"};
unsigned char code PY_mb_lian  []={"Á¬Á±Á¯Á°Á«ÁªÁ®Á­Á²Á³Á·Á¶ÁµÁ´"};
unsigned char code PY_mb_liang []={"Á©Á¼Á¹ÁºÁ¸Á»Á½ÁÁÁÂÁ¾ÁÀÁ¿"};
unsigned char code PY_mb_liao  []={"ÁÊÁÉÁÆÁÄÁÅÁÈÁÎÁÃÁÇÁÍÁÏÁÌ"};
unsigned char code PY_mb_lie   []={"ÁĞÁÓÁÒÁÔÁÑ"};
unsigned char code PY_mb_lin   []={"ÁÚÁÖÁÙÁÜÁÕÁØÁ×ÁÛÁİÁßÁŞÁà"};
unsigned char code PY_mb_ling  []={"ÁæÁéÁëÁáÁèÁåÁêÁçÁâÁãÁäÁìÁîÁí"};
unsigned char code PY_mb_liu   []={"ÁïÁõÁ÷ÁôÁğÁòÁóÁñÁöÁøÁù"};
unsigned char code PY_mb_long  []={"ÁúÁüÁıÁûÂ¡ÁşÂ¤Â¢Â£"};
unsigned char code PY_mb_lou   []={"Â¦Â¥Â§Â¨ÂªÂ©"};
unsigned char code PY_mb_lu    []={"Â¶Â¬Â®Â«Â¯Â­Â±Â²Â°Â³Â½Â¼Â¸Â¹Â»ÂµÂ·Â¾ÂºÂ´"};
unsigned char code PY_mb_luan  []={"ÂÏÂÍÂÎÂĞÂÑÂÒ"};
unsigned char code PY_mb_lue   []={"ÂÓÂÔ"};
unsigned char code PY_mb_lun   []={"ÂÕÂØÂ×ÂÙÂÚÂÖÂÛ"};
unsigned char code PY_mb_luo   []={"ÂŞÂÜÂßÂàÂáÂâÂİÂãÂåÂçÂæÂä"};
unsigned char code PY_mb_lv    []={"ÂËÂ¿ÂÀÂÂÂÃÂÁÂÅÂÆÂÄÂÉÂÇÂÊÂÌÂÈ"};
unsigned char code PY_mb_ma    []={"ÂèÂéÂíÂêÂëÂìÂîÂğÂï"};
unsigned char code PY_mb_mai   []={"ÂñÂòÂõÂóÂôÂö"};
unsigned char code PY_mb_man   []={"ÂùÂøÂ÷ÂúÂüÃ¡ÂıÂşÂû"};
unsigned char code PY_mb_mang  []={"Ã¦Ã¢Ã¤Ã£Ã§Ã¥"};
unsigned char code PY_mb_mao   []={"Ã¨Ã«Ã¬Ã©ÃªÃ®Ã­Ã¯Ã°Ã³Ã±Ã²"};
unsigned char code PY_mb_me    []={"Ã´"};
unsigned char code PY_mb_mei   []={"Ã»Ã¶ÃµÃ¼Ã·Ã½ÃºÃ¸Ã¹Ã¿ÃÀÃ¾ÃÃÃÁÃÄÃÂ"};
unsigned char code PY_mb_men   []={"ÃÅÃÆÃÇ"};
unsigned char code PY_mb_meng  []={"ÃÈÃËÃÊÃÍÃÉÃÌÃÏÃÎ"};
unsigned char code PY_mb_mi    []={"ÃÖÃÔÃÕÃÑÃÓÃÒÃ×ÃĞÃÚÃÙÃØÃÜÃİÃÛ"};
unsigned char code PY_mb_mian  []={"ÃßÃàÃŞÃâÃãÃäÃáÃåÃæ"};
unsigned char code PY_mb_miao  []={"ÃçÃèÃéÃëÃìÃêÃîÃí"};
unsigned char code PY_mb_mie   []={"ÃğÃï"};
unsigned char code PY_mb_min   []={"ÃñÃóÃòÃöÃõÃô"};
unsigned char code PY_mb_ming  []={"ÃûÃ÷ÃùÃúÃøÃü"};
unsigned char code PY_mb_miu   []={"Ãı"};
unsigned char code PY_mb_mo    []={"ºÑÃşÄ¡Ä£Ä¤Ä¦Ä¥Ä¢Ä§Ä¨Ä©Ä­Ä°ÄªÄ¯Ä®Ä«Ä¬"};
unsigned char code PY_mb_mou   []={"Ä²Ä±Ä³"};
unsigned char code PY_mb_mu    []={"Ä¸Ä¶ÄµÄ·Ä´Ä¾Ä¿ÄÁÄ¼Ä¹Ä»ÄÀÄ½ÄºÄÂ"};
unsigned char code PY_mb_na    []={"ÄÃÄÄÄÇÄÉÄÈÄÆÄÅ"};
unsigned char code PY_mb_nai   []={"ÄËÄÌÄÊÄÎÄÍ"};
unsigned char code PY_mb_nan   []={"ÄĞÄÏÄÑ"};
unsigned char code PY_mb_nang  []={"ÄÒ"};
unsigned char code PY_mb_nao   []={"ÄÓÄÕÄÔÄÖÄ×"};
unsigned char code PY_mb_ne    []={"ÄØ"};
unsigned char code PY_mb_nei   []={"ÄÚÄÙ"};
unsigned char code PY_mb_nen   []={"ÄÛ"};
unsigned char code PY_mb_neng  []={"ÄÜ"};
unsigned char code PY_mb_ni    []={"ÄİÄáÄàÄßÄŞÄãÄâÄæÄäÄçÄå"};
unsigned char code PY_mb_nian  []={"ÄéÄêÄíÄìÄëÄîÄè"};
unsigned char code PY_mb_niang []={"ÄïÄğ"};
unsigned char code PY_mb_niao  []={"ÄñÄò"};
unsigned char code PY_mb_nie   []={"ÄóÄùÄôÄöÄ÷ÄøÄõ"};
unsigned char code PY_mb_nin   []={"Äú"};
unsigned char code PY_mb_ning  []={"ÄşÅ¡ÄüÄûÄıÅ¢"};
unsigned char code PY_mb_niu   []={"Å£Å¤Å¦Å¥"};
unsigned char code PY_mb_nong  []={"Å©Å¨Å§Åª"};
unsigned char code PY_mb_nu    []={"Å«Å¬Å­"};
unsigned char code PY_mb_nuan  []={"Å¯"};
unsigned char code PY_mb_nue   []={"Å±Å°"};
unsigned char code PY_mb_nuo   []={"Å²ÅµÅ³Å´"};
unsigned char code PY_mb_nv    []={"Å®"};
unsigned char code PY_mb_o     []={"Å¶"};
unsigned char code PY_mb_ou    []={"Å·Å¹Å¸Å»Å¼ÅºÅ½"};
unsigned char code PY_mb_pa    []={"Å¿Å¾ÅÀ°ÒÅÃÅÁÅÂ"};
unsigned char code PY_mb_pai   []={"ÅÄÅÇÅÅÅÆÅÉÅÈ"};
unsigned char code PY_mb_pan   []={"ÅËÅÊÅÌÅÍÅĞÅÑÅÎÅÏ"};
unsigned char code PY_mb_pang  []={"ÅÒÅÓÅÔÅÕÅÖ"};
unsigned char code PY_mb_pao   []={"Å×ÅÙÅØÅÚÅÛÅÜÅİ"};
unsigned char code PY_mb_pei   []={"ÅŞÅßÅãÅàÅâÅáÅæÅåÅä"};
unsigned char code PY_mb_pen   []={"ÅçÅè"};
unsigned char code PY_mb_peng  []={"ÅêÅéÅëÅóÅíÅïÅğÅîÅôÅìÅñÅòÅõÅö"};
unsigned char code PY_mb_pi    []={"±ÙÅúÅ÷ÅûÅøÅüÅùÆ¤ÅşÆ£Æ¡ÅıÆ¢Æ¥Æ¦Æ¨Æ§Æ©"};
unsigned char code PY_mb_pian  []={"Æ¬Æ«ÆªÆ­"};
unsigned char code PY_mb_piao  []={"Æ¯Æ®Æ°Æ±"};
unsigned char code PY_mb_pie   []={"Æ²Æ³"};
unsigned char code PY_mb_pin   []={"Æ´Æ¶ÆµÆ·Æ¸"};
unsigned char code PY_mb_ping  []={"Æ¹Æ½ÆÀÆ¾ÆºÆ»ÆÁÆ¿Æ¼"};
unsigned char code PY_mb_po    []={"ÆÂÆÃÆÄÆÅÆÈÆÆÆÉÆÇ"};
unsigned char code PY_mb_pou   []={"ÆÊ"};
unsigned char code PY_mb_pu    []={"¸¬ÆÍÆËÆÌÆÎÆĞÆÏÆÑÆÓÆÔÆÒÆÖÆÕÆ×ÆØ"};
unsigned char code PY_mb_qi    []={"ÆßÆãÆŞÆâÆàÆÜÆİÆÚÆÛÆáÆîÆëÆäÆæÆçÆíÆêÆéÆèÆïÆåÆìÆòÆóÆñÆôÆğÆøÆıÆùÆúÆûÆüÆõÆöÆ÷"};
unsigned char code PY_mb_qia   []={"ÆşÇ¡Ç¢"};
unsigned char code PY_mb_qian  []={"Ç§ÇªÇ¤Ç¨Ç¥Ç£Ç¦Ç«Ç©Ç°Ç®Ç¯Ç¬Ç±Ç­Ç³Ç²Ç´Ç·ÇµÇ¶Ç¸"};
unsigned char code PY_mb_qiang []={"ÇºÇ¼Ç¹Ç»Ç¿Ç½Ç¾ÇÀ"};
unsigned char code PY_mb_qiao  []={"ÇÄÇÃÇÂÇÁÇÇÇÈÇÅÇÆÇÉÇÎÇÍÇÏÇÌÇËÇÊ"};
unsigned char code PY_mb_qie   []={"ÇĞÇÑÇÒÇÓÇÔ"};
unsigned char code PY_mb_qin   []={"Ç×ÇÖÇÕÇÛÇØÇÙÇİÇÚÇÜÇŞÇß"};
unsigned char code PY_mb_qing  []={"ÇàÇâÇáÇãÇäÇåÇéÇçÇèÇæÇêÇëÇì"};
unsigned char code PY_mb_qiong []={"ÇîÇí"};
unsigned char code PY_mb_qiu   []={"ÇğÇñÇïÇôÇóÇöÇõÇò"};
unsigned char code PY_mb_qu    []={"ÇøÇúÇıÇüÇùÇûÇ÷ÇşÈ¡È¢È£È¥È¤"};
unsigned char code PY_mb_quan  []={"È¦È«È¨ÈªÈ­È¬È©È§È®È°È¯"};
unsigned char code PY_mb_que   []={"È²È±È³È´È¸È·ÈµÈ¶"};
unsigned char code PY_mb_qun   []={"È¹Èº"};
unsigned char code PY_mb_ran   []={"È»È¼È½È¾"};
unsigned char code PY_mb_rang  []={"È¿ÈÂÈÀÈÁÈÃ"};
unsigned char code PY_mb_rao   []={"ÈÄÈÅÈÆ"};
unsigned char code PY_mb_re    []={"ÈÇÈÈ"};
unsigned char code PY_mb_ren   []={"ÈËÈÊÈÉÈÌÈĞÈÏÈÎÈÒÈÑÈÍ"};
unsigned char code PY_mb_reng  []={"ÈÓÈÔ"};
unsigned char code PY_mb_ri    []={"ÈÕ"};
unsigned char code PY_mb_rong  []={"ÈÖÈŞÈ×ÈÙÈİÈÜÈØÈÛÈÚÈß"};
unsigned char code PY_mb_rou   []={"ÈáÈàÈâ"};
unsigned char code PY_mb_ru    []={"ÈçÈãÈåÈæÈäÈêÈéÈèÈëÈì"};
unsigned char code PY_mb_ruan  []={"ÈîÈí"};
unsigned char code PY_mb_rui   []={"ÈïÈñÈğ"};
unsigned char code PY_mb_run   []={"ÈòÈó"};
unsigned char code PY_mb_ruo   []={"ÈôÈõ"};
unsigned char code PY_mb_sa    []={"ÈöÈ÷Èø"};
unsigned char code PY_mb_sai   []={"ÈûÈùÈúÈü"};
unsigned char code PY_mb_san   []={"ÈıÈşÉ¡É¢"};
unsigned char code PY_mb_sang  []={"É£É¤É¥"};
unsigned char code PY_mb_sao   []={"É¦É§É¨É©"};
unsigned char code PY_mb_se    []={"É«É¬Éª"};
unsigned char code PY_mb_sen   []={"É­"};
unsigned char code PY_mb_seng  []={"É®"};
unsigned char code PY_mb_sha   []={"É±É³É´É°É¯ÉµÉ¶É·ÏÃ"};
unsigned char code PY_mb_shai  []={"É¸É¹"};
unsigned char code PY_mb_shan  []={"É½É¾É¼ÉÀÉºÉ¿ÉÁÉÂÉÇÉ»ÉÈÉÆÉÉÉÃÉÅÉÄÕ¤"};
unsigned char code PY_mb_shang []={"ÉËÉÌÉÊÉÑÉÎÉÍÉÏÉĞ"};
unsigned char code PY_mb_shao  []={"ÉÓÉÒÉÕÉÔÉ×ÉÖÉØÉÙÉÛÉÜÉÚ"};
unsigned char code PY_mb_she   []={"ÉİÉŞÉàÉßÉáÉèÉçÉäÉæÉâÉåÉã"};
unsigned char code PY_mb_shen  []={"ÉêÉìÉíÉëÉğÉïÉéÉîÉñÉòÉóÉôÉöÉõÉøÉ÷Ê²"};
unsigned char code PY_mb_sheng []={"ÉıÉúÉùÉüÊ¤ÉûÉşÊ¡Ê¥Ê¢Ê£"};
unsigned char code PY_mb_shi   []={"³×Ê¬Ê§Ê¦Ê­Ê«Ê©Ê¨ÊªÊ®Ê¯Ê±Ê¶ÊµÊ°Ê´Ê³Ê·Ê¸Ê¹Ê¼Ê»ÊºÊ¿ÊÏÊÀÊËÊĞÊ¾Ê½ÊÂÊÌÊÆÊÓÊÔÊÎÊÒÊÑÊÃÊÇÊÁÊÊÊÅÊÍÊÈÊÄÊÉËÆ"};
unsigned char code PY_mb_shou  []={"ÊÕÊÖÊØÊ×ÊÙÊÜÊŞÊÛÊÚÊİ"};
unsigned char code PY_mb_shu   []={"ÊéÊãÊåÊàÊâÊáÊçÊèÊæÊäÊßÊëÊêÊìÊîÊòÊğÊóÊñÊíÊïÊõÊùÊøÊöÊ÷ÊúË¡ÊüÊıÊûÊşÊô"};
unsigned char code PY_mb_shua  []={"Ë¢Ë£"};
unsigned char code PY_mb_shuai []={"Ë¥Ë¤Ë¦Ë§"};
unsigned char code PY_mb_shuan []={"Ë©Ë¨"};
unsigned char code PY_mb_shuang[]={"Ë«ËªË¬"};
unsigned char code PY_mb_shui  []={"Ë­Ë®Ë°Ë¯"};
unsigned char code PY_mb_shun  []={"Ë±Ë³Ë´Ë²"};
unsigned char code PY_mb_shuo  []={"ËµË¸Ë·Ë¶"};
unsigned char code PY_mb_si    []={"Ë¿Ë¾Ë½Ë¼Ë¹Ë»ËºËÀËÈËÄËÂËÅËÇËÃËÁ"};
unsigned char code PY_mb_song  []={"ËÉËËËÊËÏËÎËĞËÍËÌ"};
unsigned char code PY_mb_sou   []={"ËÔËÑËÒËÓ"};
unsigned char code PY_mb_su    []={"ËÕËÖË×ËßËàËØËÙËÚËÜËİËÛ"};
unsigned char code PY_mb_suan  []={"ËáËâËã"};
unsigned char code PY_mb_sui   []={"ËäËçËåËæËèËêËîËìËéËíËë"};
unsigned char code PY_mb_sun   []={"ËïËğËñ"};
unsigned char code PY_mb_suo   []={"ËôËóËòËõËùË÷ËöËø"};
unsigned char code PY_mb_ta    []={"ËıËûËüËúËşÌ¡Ì¢Ì¤Ì£"};
unsigned char code PY_mb_tai   []={"Ì¥Ì¨Ì§Ì¦Ì«Ì­Ì¬Ì©Ìª"};
unsigned char code PY_mb_tan   []={"Ì®Ì°Ì¯Ì²Ì±Ì³Ì¸ÌµÌ·Ì¶Ì´Ì¹Ì»ÌºÌ¾Ì¿Ì½Ì¼"};
unsigned char code PY_mb_tang  []={"ÌÀÌÆÌÃÌÄÌÁÌÂÌÅÌÇÌÈÌÊÌÉÌÌÌË"};
unsigned char code PY_mb_tao   []={"ÌÎÌĞÌÍÌÏÌÓÌÒÌÕÌÔÌÑÌÖÌ×"};
unsigned char code PY_mb_te    []={"ÌØ"};
unsigned char code PY_mb_teng  []={"ÌÛÌÚÌÜÌÙ"};
unsigned char code PY_mb_ti    []={"ÌŞÌİÌàÌßÌäÌáÌâÌãÌåÌëÌêÌéÌèÌæÌç"};
unsigned char code PY_mb_tian  []={"ÌìÌíÌïÌñÌğÌîÌóÌò"};
unsigned char code PY_mb_tiao  []={"µ÷ÌôÌõÌöÌ÷Ìø"};
unsigned char code PY_mb_tie   []={"ÌùÌúÌû"};
unsigned char code PY_mb_ting  []={"ÌüÍ¡ÌıÌşÍ¢Í¤Í¥Í£Í¦Í§"};
unsigned char code PY_mb_tong  []={"Í¨Í¬Í®Í©Í­Í¯ÍªÍ«Í³Í±Í°Í²Í´"};
unsigned char code PY_mb_tou   []={"ÍµÍ·Í¶Í¸"};
unsigned char code PY_mb_tu    []={"Í¹ÍºÍ»Í¼Í½Í¿Í¾ÍÀÍÁÍÂÍÃ"};
unsigned char code PY_mb_tuan  []={"ÍÄÍÅ"};
unsigned char code PY_mb_tui   []={"ÍÆÍÇÍÈÍËÍÉÍÊ"};
unsigned char code PY_mb_tun   []={"¶ÚÍÌÍÍÍÎ"};
unsigned char code PY_mb_tuo   []={"ÍĞÍÏÍÑÍÔÍÓÍÕÍÒÍ×ÍÖÍØÍÙ"};
unsigned char code PY_mb_wa    []={"ÍÛÍŞÍÚÍİÍÜÍßÍà"};
unsigned char code PY_mb_wai   []={"ÍáÍâ"};
unsigned char code PY_mb_wan   []={"ÍäÍåÍãÍèÍêÍæÍçÍéÍğÍìÍíÍñÍïÍîÍëÍòÍó"};
unsigned char code PY_mb_wang  []={"ÍôÍöÍõÍøÍùÍ÷ÍıÍüÍúÍû"};
unsigned char code PY_mb_wei   []={"Î£ÍşÎ¢Î¡ÎªÎ¤Î§Î¥Î¦Î¨Î©Î¬Î«Î°Î±Î²Î³Î­Î¯Î®ÎÀÎ´Î»Î¶Î·Î¸Î¾Î½Î¹Î¼ÎµÎ¿Îº"};
unsigned char code PY_mb_wen   []={"ÎÂÎÁÎÄÎÆÎÅÎÃÎÇÎÉÎÈÎÊ"};
unsigned char code PY_mb_weng  []={"ÎÌÎËÎÍ"};
unsigned char code PY_mb_wo    []={"ÎÎÎĞÎÑÎÏÎÒÎÖÎÔÎÕÎÓ"};
unsigned char code PY_mb_wu    []={"ÎÚÎÛÎØÎ×ÎİÎÜÎÙÎŞÎãÎâÎáÎßÎàÎåÎçÎéÎëÎäÎêÎæÎèÎğÎñÎìÎïÎóÎòÎîÎí"};
unsigned char code PY_mb_xi    []={"Ï¦Ï«Î÷ÎüÏ£ÎôÎöÎùÏ¢ÎşÏ¤Ï§Ï©ÎøÎúÏ¬Ï¡ÏªÎıÏ¨ÎõÎûÏ¥Ï°Ï¯Ï®Ï±Ï­Ï´Ï²Ï·ÏµÏ¸Ï¶"};
unsigned char code PY_mb_xia   []={"ÏºÏ¹Ï»ÏÀÏ¿ÏÁÏ¾Ï½Ï¼ÏÂÏÅÏÄ"};
unsigned char code PY_mb_xian  []={"Ï³ÏÉÏÈÏËÏÆÏÇÏÊÏĞÏÒÏÍÏÌÏÑÏÏÏÎÏÓÏÔÏÕÏØÏÖÏßÏŞÏÜÏİÏÚÏÛÏ×ÏÙ"};
unsigned char code PY_mb_xiang []={"ÏçÏàÏãÏáÏæÏäÏåÏâÏêÏéÏèÏíÏìÏëÏòÏïÏîÏóÏñÏğ"};
unsigned char code PY_mb_xiao  []={"ÏüÏûÏôÏõÏúÏöÏùÏıĞ¡ÏşĞ¢Ğ¤ÏøĞ§Ğ£Ğ¦Ğ¥"};
unsigned char code PY_mb_xie   []={"Ğ©Ğ¨ĞªĞ«Ğ­Ğ°Ğ²Ğ±Ğ³Ğ¯Ğ¬Ğ´Ğ¹ĞºĞ¶Ğ¼ĞµĞ»Ğ¸Ğ·"};
unsigned char code PY_mb_xin   []={"ĞÄĞÃĞ¾ĞÁĞÀĞ¿ĞÂĞ½ĞÅĞÆ"};
unsigned char code PY_mb_xing  []={"ĞËĞÇĞÊĞÉĞÈĞÌĞÏĞÎĞÍĞÑĞÓĞÕĞÒĞÔ"};
unsigned char code PY_mb_xiong []={"Ğ×ĞÖĞÙĞÚĞØĞÛĞÜ"};
unsigned char code PY_mb_xiu   []={"ËŞĞİĞŞĞßĞàĞãĞåĞäĞâĞá"};
unsigned char code PY_mb_xu    []={"ĞçĞëĞéĞêĞèĞæĞìĞíĞñĞòĞğĞôĞ÷ĞøĞïĞöĞõĞîÓõ"};
unsigned char code PY_mb_xuan  []={"ĞùĞûĞúĞşĞüĞıÑ¡Ñ¢Ñ¤Ñ£"};
unsigned char code PY_mb_xue   []={"Ï÷Ñ¥Ñ¦Ñ¨Ñ§Ñ©Ñª"};
unsigned char code PY_mb_xun   []={"Ñ«Ñ¬Ñ°Ñ²Ñ®Ñ±Ñ¯Ñ­ÑµÑ¶Ñ´Ñ¸Ñ·Ñ³"};
unsigned char code PY_mb_ya    []={"Ñ¾Ñ¹Ñ½ÑºÑ»Ñ¼ÑÀÑ¿ÑÁÑÂÑÄÑÃÑÆÑÅÑÇÑÈ"};
unsigned char code PY_mb_yan   []={"ÑÊÑÌÑÍÑÉÑËÑÓÑÏÑÔÑÒÑØÑ×ÑĞÑÎÑÖÑÑÑÕÑÙÑÜÑÚÑÛÑİÑáÑåÑâÑäÑçÑŞÑéÑèÑßÑæÑãÑà"};
unsigned char code PY_mb_yang  []={"ÑëÑêÑíÑìÑïÑòÑôÑîÑğÑñÑóÑöÑøÑõÑ÷ÑùÑú"};
unsigned char code PY_mb_yao   []={"½ÄÑıÑüÑûÒ¢Ò¦Ò¤Ò¥Ò¡Ò£ÑşÒ§Ò¨Ò©ÒªÒ«Ô¿"};
unsigned char code PY_mb_ye    []={"Ò¬Ò­Ò¯Ò®Ò²Ò±Ò°ÒµÒ¶Ò·Ò³Ò¹Ò´ÒºÒ¸"};
unsigned char code PY_mb_yi    []={"Ò»ÒÁÒÂÒ½ÒÀÒ¿Ò¼Ò¾ÒÇÒÄÒÊÒËÒÌÒÈÒÆÒÅÒÃÒÉÒÍÒÒÒÑÒÔÒÓÒÏÒĞÒÎÒåÒÚÒäÒÕÒéÒàÒÙÒìÒÛÒÖÒëÒØÒ×ÒïÒèÒßÒæÒêÒîÒİÒâÒçÒŞÒáÒãÒíÒÜ"};
unsigned char code PY_mb_yin   []={"ÒòÒõÒöÒğÒñÒôÒóÒ÷ÒúÒùÒøÒüÒıÒûÒşÓ¡"};
unsigned char code PY_mb_ying  []={"Ó¦Ó¢Ó¤Ó§Ó£Ó¥Ó­Ó¯Ó«Ó¨Ó©ÓªÓ¬Ó®Ó±Ó°Ó³Ó²"};
unsigned char code PY_mb_yo    []={"Ó´"};
unsigned char code PY_mb_yong  []={"Ó¶ÓµÓ¸Ó¹ÓºÓ·ÓÀÓ½Ó¾ÓÂÓ¿ÓÁÓ¼Ó»ÓÃ"};
unsigned char code PY_mb_you   []={"ÓÅÓÇÓÄÓÆÓÈÓÉÓÌÓÊÓÍÓËÓÎÓÑÓĞÓÏÓÖÓÒÓ×ÓÓÓÕÓÔ"};
unsigned char code PY_mb_yu    []={"ÓØÓÙÓåÓÚÓèÓàÓÛÓãÓáÓéÓæÓçÓäÓâÓŞÓÜÓİÓßÓëÓîÓìÓğÓêÓíÓïÓñÔ¦ÓóÓıÓôÓüÓøÔ¡Ô¤ÓòÓûÓ÷Ô¢ÓùÔ£ÓöÓúÓşÔ¥"};
unsigned char code PY_mb_yuan  []={"Ô©Ô§Ô¨ÔªÔ±Ô°Ô«Ô­Ô²Ô¬Ô®ÔµÔ´Ô³Ô¯Ô¶Ô·Ô¹ÔºÔ¸"};
unsigned char code PY_mb_yue   []={"Ô»Ô¼ÔÂÔÀÔÃÔÄÔ¾ÔÁÔ½"};
unsigned char code PY_mb_yun   []={"ÔÆÔÈÔÇÔÅÔÊÔÉÔĞÔËÔÎÔÍÔÏÔÌ"};
unsigned char code PY_mb_za    []={"ÔÑÔÓÔÒÕ¦"};
unsigned char code PY_mb_zai   []={"ÔÖÔÕÔÔÔ×ÔØÔÙÔÚ×Ğ"};
unsigned char code PY_mb_zan   []={"ÔÛÔÜÔİÔŞ"};
unsigned char code PY_mb_zang  []={"ÔßÔàÔá"};
unsigned char code PY_mb_zao   []={"ÔâÔãÔäÔçÔæÔéÔèÔåÔîÔíÔìÔëÔïÔê"};
unsigned char code PY_mb_ze    []={"ÔòÔñÔóÔğ"};
unsigned char code PY_mb_zei   []={"Ôô"};
unsigned char code PY_mb_zen   []={"Ôõ"};
unsigned char code PY_mb_zeng  []={"ÔöÔ÷Ôù"};
unsigned char code PY_mb_zha   []={"ÔûÔüÔúÔıÔşÕ¢Õ¡Õ£Õ§Õ©Õ¨Õ¥×õ"};
unsigned char code PY_mb_zhai  []={"Õ«ÕªÕ¬µÔÕ­Õ®Õ¯"};
unsigned char code PY_mb_zhan  []={"Õ´Õ±Õ³Õ²Õ°Õ¶Õ¹ÕµÕ¸Õ·Õ¼Õ½Õ»Õ¾ÕÀÕ¿Õº"};
unsigned char code PY_mb_zhang []={"³¤ÕÅÕÂÕÃÕÄÕÁÕÇÕÆÕÉÕÌÕÊÕÈÕÍÕËÕÏÕÎ"};
unsigned char code PY_mb_zhao  []={"ÕĞÕÑÕÒÕÓÕÙÕ×ÕÔÕÕÕÖÕØ×¦"};
unsigned char code PY_mb_zhe   []={"ÕÚÕÛÕÜÕİÕŞÕßÕàÕâÕãÕá×Å"};
unsigned char code PY_mb_zhen  []={"ÕêÕëÕìÕäÕæÕèÕåÕçÕéÕïÕíÕîÕóÕñÕòÕğÖ¡"};
unsigned char code PY_mb_zheng []={"ÕùÕ÷ÕúÕõÕøÕöÕôÕüÕûÕıÖ¤Ö£ÕşÖ¢"};
unsigned char code PY_mb_zhi   []={"Ö®Ö§Ö­Ö¥Ö¨Ö¦ÖªÖ¯Ö«Ö¬Ö©Ö´Ö¶Ö±ÖµÖ°Ö²Ö³Ö¹Ö»Ö¼Ö·Ö½Ö¸ÖºÖÁÖ¾ÖÆÖÄÖÎÖËÖÊÖÅÖ¿ÖÈÖÂÖÀÖÌÖÏÖÇÖÍÖÉÖÃ"};
unsigned char code PY_mb_zhong []={"ÖĞÖÒÖÕÖÑÖÓÖÔÖ×ÖÖÖÙÖÚÖØ"};
unsigned char code PY_mb_zhou  []={"ÖİÖÛÖßÖÜÖŞÖàÖáÖâÖãÖäÖæÖçÖåÖè"};
unsigned char code PY_mb_zhu   []={"ÖìÖïÖêÖéÖîÖíÖëÖñÖòÖğÖ÷ÖôÖóÖöÖõ×¡Öú×¢Öü×¤Öù×£ÖøÖûÖşÖı"};
unsigned char code PY_mb_zhua  []={"×¥"};
unsigned char code PY_mb_zhuai []={"×§"};
unsigned char code PY_mb_zhuan []={"×¨×©×ª×«×­"};
unsigned char code PY_mb_zhuang[]={"×±×¯×®×°×³×´´±×²"};
unsigned char code PY_mb_zhui  []={"×·×µ×¶×¹×º×¸"};
unsigned char code PY_mb_zhun  []={"×»×¼"};
unsigned char code PY_mb_zhuo  []={"×¿×¾×½×À×Æ×Â×Ç×Ã×Ä×Á"};
unsigned char code PY_mb_zi    []={"×Î×È×É×Ë×Ê×Í×Ì×Ñ×Ó×Ï×Ò×Ö×Ô×Õ"};
unsigned char code PY_mb_zong  []={"×Ú×Û×Ø×Ù×××Ü×İ"};
unsigned char code PY_mb_zou   []={"×Ş×ß×à×á"};
unsigned char code PY_mb_zu    []={"×â×ã×ä×å×ç×è×é×æ"};
unsigned char code PY_mb_zuan  []={"×¬×ë×ê"};
unsigned char code PY_mb_zui   []={"×ì×î×ï×í"};
unsigned char code PY_mb_zun   []={"×ğ×ñ"};
unsigned char code PY_mb_zuo   []={"×ò×ó×ô×÷×ø×ù×ö"};

//================================================================================================


//"Æ´ÒôÊäÈë·¨²éÑ¯Âë±í"

unsigned char code PY_index_a[][8]={
  							{"     ",0x00,0x00},
  							{"i    ",0x05,0x00},
  							{"n    ",0x20,0x00},
  							{"ng   ",0x33,0x00},
  							{"o    ",0x3A,0x00}};
unsigned char code PY_index_b[][8]={
  							{"a    ",0x4D,0x00},
  							{"ai   ",0x70,0x00},
  							{"an   ",0x81,0x00},
  							{"ang  ",0xA0,0x00},
  							{"ao   ",0xB9,0x00},
  							{"ei   ",0xDE,0x00},
  							{"en   ",0xFD,0x00},
  							{"eng  ",0x08,0x01},
  							{"i    ",0x15,0x01},
  							{"ian  ",0x44,0x01},
  							{"iao  ",0x5D,0x01},
  							{"ie   ",0x66,0x01},
  							{"in   ",0x6F,0x01},
  							{"ing  ",0x7C,0x01},
  							{"o    ",0x8F,0x01},
  							{"u    ",0xB8,0x01}};
unsigned char code PY_index_c[][8]={
  							{"a    ",0xCD,0x01},
  							{"ai   ",0xD0,0x01},
  							{"an   ",0xE7,0x01},
  							{"ang  ",0xF6,0x01},
  							{"ao   ",0x01,0x02},
  							{"e    ",0x0C,0x02},
  							{"eng  ",0x17,0x02},
  							{"ha   ",0x1E,0x02},
  							{"hai  ",0x37,0x02},
  							{"han  ",0x3E,0x02},
  							{"hang ",0x53,0x02},
  							{"hao  ",0x6C,0x02},
  							{"he   ",0x81,0x02},
  							{"hen  ",0x8E,0x02},
  							{"heng ",0xA3,0x02},
  							{"hi   ",0xC2,0x02},
  							{"hong ",0xE1,0x02},
  							{"hou  ",0xEC,0x02},
  							{"hu   ",0x05,0x03},
  							{"huai ",0x28,0x03},
  							{"huan ",0x2B,0x03},
  							{"huang",0x3A,0x03},
  							{"hui  ",0x45,0x03},
  							{"hun  ",0x50,0x03},
  							{"huo  ",0x5F,0x03},
  							{"i    ",0x62,0x03},
  							{"ong  ",0x7B,0x03},
  							{"ou   ",0x88,0x03},
  							{"u    ",0x8B,0x03},
  							{"uan  ",0x94,0x03},
  							{"ui   ",0x9B,0x03},
  							{"un   ",0xAC,0x03},
  							{"uo   ",0xB3,0x03}};
unsigned char code PY_index_d[][8]={
  							{"a    ",0xC0,0x03},
  							{"ai   ",0xCD,0x03},
  							{"an   ",0xE6,0x03},
  							{"ang  ",0x05,0x04},
  							{"ao   ",0x10,0x04},
  							{"e    ",0x29,0x04},
  							{"eng  ",0x30,0x04},
  							{"i    ",0x3F,0x04},
  							{"ian  ",0x64,0x04},
  							{"iao  ",0x85,0x04},
  							{"ie   ",0x96,0x04},
  							{"ing  ",0xA5,0x04},
  							{"iu   ",0xB8,0x04},
  							{"ong  ",0xBB,0x04},
  							{"ou   ",0xD0,0x04},
  							{"u    ",0xE1,0x04},
  							{"uan  ",0xFE,0x04},
  							{"ui   ",0x0B,0x05},
  							{"un   ",0x14,0x05},
  							{"uo   ",0x25,0x05}};
unsigned char code PY_index_e[][8]={
  							{"     ",0x3E,0x05},
  							{"n    ",0x59,0x05},
  							{"r    ",0x5C,0x05}};
unsigned char code PY_index_f[][8]={
  							{"a    ",0x6D,0x05},
  							{"an   ",0x7E,0x05},
  							{"ang  ",0xA1,0x05},
  							{"ei   ",0xB8,0x05},
  							{"en   ",0xD1,0x05},
  							{"eng  ",0xF0,0x05},
  							{"o    ",0x0F,0x06},
  							{"ou   ",0x12,0x06},
  							{"u    ",0x15,0x06}};
unsigned char code PY_index_g[][8]={
  							{"a    ",0x6E,0x06},
  							{"ai   ",0x73,0x06},
  							{"an   ",0x80,0x06},
  							{"ang  ",0x97,0x06},
  							{"ao   ",0xAA,0x06},
  							{"e    ",0xBF,0x06},
  							{"ei   ",0xE2,0x06},
  							{"en   ",0xE5,0x06},
  							{"eng  ",0xEA,0x06},
  							{"ong  ",0xF9,0x06},
  							{"ou   ",0x18,0x07},
  							{"u    ",0x2B,0x07},
  							{"ua   ",0x50,0x07},
  							{"uai  ",0x5D,0x07},
  							{"uan  ",0x64,0x07},
  							{"uang ",0x7B,0x07},
  							{"ui   ",0x82,0x07},
  							{"un   ",0xA3,0x07},
  							{"uo   ",0xAA,0x07}};
unsigned char code PY_index_h[][8]={
  							{"a    ",0xB7,0x07},
  							{"ai   ",0xBC,0x07},
  							{"an   ",0xCB,0x07},
  							{"ang  ",0xF2,0x07},
  							{"ao   ",0xF9,0x07},
  							{"e    ",0x0C,0x08},
  							{"ei   ",0x2F,0x08},
  							{"en   ",0x34,0x08},
  							{"eng  ",0x3D,0x08},
  							{"ong  ",0x48,0x08},
  							{"ou   ",0x5B,0x08},
  							{"u    ",0x6A,0x08},
  							{"ua   ",0x8F,0x08},
  							{"uai  ",0xA2,0x08},
  							{"uan  ",0xAD,0x08},
  							{"uang ",0xCA,0x08},
  							{"ui   ",0xE7,0x08},
  							{"un   ",0x12,0x09},
  							{"uo   ",0x1F,0x09}};
unsigned char code PY_index_j[][8]={
  							{"i    ",0x34,0x09},
  							{"ia   ",0xA1,0x09},
  							{"ian  ",0xC6,0x09},
  							{"iang ",0x15,0x0A},
  							{"iao  ",0x30,0x0A},
  							{"ie   ",0x69,0x0A},
  							{"in   ",0x9C,0x0A},
  							{"ing  ",0xC5,0x0A},
  							{"iong ",0xF8,0x0A},
  							{"iu   ",0xFD,0x0A},
  							{"u    ",0x20,0x0B},
  							{"uan  ",0x55,0x0B},
  							{"ue   ",0x64,0x0B},
  							{"un   ",0x77,0x0B}};
unsigned char code PY_index_k[][8]={
  							{"a    ",0x8E,0x0B},
  							{"ai   ",0x95,0x0B},
  							{"an   ",0xA0,0x0B},
  							{"ang  ",0xAF,0x0B},
  							{"ao   ",0xBE,0x0B},
  							{"e    ",0xC7,0x0B},
  							{"en   ",0xE6,0x0B},
  							{"eng  ",0xEF,0x0B},
  							{"ong  ",0xF4,0x0B},
  							{"ou   ",0xFD,0x0B},
  							{"u    ",0x06,0x0C},
  							{"ua   ",0x15,0x0C},
  							{"uai  ",0x20,0x0C},
  							{"uan  ",0x29,0x0C},
  							{"uang ",0x2E,0x0C},
  							{"ui   ",0x3F,0x0C},
  							{"un   ",0x56,0x0C},
  							{"uo   ",0x5F,0x0C}};
unsigned char code PY_index_l[][8]={
  							{"a    ",0x68,0x0C},
  							{"ai   ",0x77,0x0C},
  							{"an   ",0x7E,0x0C},
  							{"ang  ",0x9D,0x0C},
  							{"ao   ",0xAC,0x0C},
  							{"e    ",0xBF,0x0C},
  							{"ei   ",0xC6,0x0C},
  							{"eng  ",0xDD,0x0C},
  							{"i    ",0xE4,0x0C},
  							{"ian  ",0x29,0x0D},
  							{"iang ",0x46,0x0D},
  							{"iao  ",0x5F,0x0D},
  							{"ie   ",0x78,0x0D},
  							{"in   ",0x83,0x0D},
  							{"ing  ",0x9C,0x0D},
  							{"iu   ",0xB9,0x0D},
  							{"ong  ",0xD0,0x0D},
  							{"ou   ",0xE3,0x0D},
  							{"u    ",0xF0,0x0D},
  							{"uan  ",0x19,0x0E},
  							{"ue   ",0x26,0x0E},
  							{"un   ",0x2B,0x0E},
  							{"uo   ",0x3A,0x0E},
  							{"v    ",0x53,0x0E}};
unsigned char code PY_index_m[][8]={
  							{"a    ",0x70,0x0E},
  							{"ai   ",0x83,0x0E},
  							{"an   ",0x90,0x0E},
  							{"ang  ",0xA3,0x0E},
  							{"ao   ",0xB0,0x0E},
  							{"e    ",0xC9,0x0E},
  							{"ei   ",0xCC,0x0E},
  							{"en   ",0xED,0x0E},
  							{"eng  ",0xF4,0x0E},
  							{"i    ",0x05,0x0F},
  							{"ian  ",0x22,0x0F},
  							{"iao  ",0x35,0x0F},
  							{"ie   ",0x46,0x0F},
  							{"in   ",0x4B,0x0F},
  							{"ing  ",0x58,0x0F},
  							{"iu   ",0x65,0x0F},
  							{"o    ",0x68,0x0F},
  							{"ou   ",0x8D,0x0F},
  							{"u    ",0x94,0x0F}};
unsigned char code PY_index_n[][8]={
  							{"a    ",0xB3,0x0F},
  							{"ai   ",0xC2,0x0F},
  							{"an   ",0xCD,0x0F},
  							{"ang  ",0xD4,0x0F},
  							{"ao   ",0xD7,0x0F},
  							{"e    ",0xE2,0x0F},
  							{"ei   ",0xE5,0x0F},
  							{"en   ",0xEA,0x0F},
  							{"eng  ",0xED,0x0F},
  							{"i    ",0xF0,0x0F},
  							{"ian  ",0x07,0x10},
  							{"iang ",0x16,0x10},
  							{"iao  ",0x1B,0x10},
  							{"ie   ",0x20,0x10},
  							{"in   ",0x2F,0x10},
  							{"ing  ",0x32,0x10},
  							{"iu   ",0x3F,0x10},
  							{"ong  ",0x48,0x10},
  							{"u    ",0x51,0x10},
  							{"uan  ",0x58,0x10},
  							{"ue   ",0x5B,0x10},
  							{"uo   ",0x60,0x10},
  							{"v    ",0x69,0x10}};
unsigned char code PY_index_o[][8]={
  							{"     ",0x6C,0x10},
  							{"u    ",0x6F,0x10}};
unsigned char code PY_index_p[][8]={
  							{"a    ",0x7E,0x10},
  							{"ai   ",0x8D,0x10},
  							{"an   ",0x9A,0x10},
  							{"ang  ",0xAB,0x10},
  							{"ao   ",0xB6,0x10},
  							{"ei   ",0xC5,0x10},
  							{"en   ",0xD8,0x10},
  							{"eng  ",0xDD,0x10},
  							{"i    ",0xFA,0x10},
  							{"ian  ",0x1F,0x11},
  							{"iao  ",0x28,0x11},
  							{"ie   ",0x31,0x11},
  							{"in   ",0x36,0x11},
  							{"ing  ",0x41,0x11},
  							{"o    ",0x54,0x11},
  							{"ou   ",0x65,0x11},
  							{"u    ",0x68,0x11}};
unsigned char code PY_index_q[][8]={
  							{"i    ",0x87,0x11},
  							{"ia   ",0xD0,0x11},
  							{"ian  ",0xD7,0x11},
  							{"iang ",0x04,0x12},
  							{"iao  ",0x15,0x12},
  							{"ie   ",0x34,0x12},
  							{"in   ",0x3F,0x12},
  							{"ing  ",0x56,0x12},
  							{"iong ",0x71,0x12},
  							{"iu   ",0x76,0x12},
  							{"u    ",0x87,0x12},
  							{"uan  ",0xA2,0x12},
  							{"ue   ",0xB9,0x12},
  							{"un   ",0xCA,0x12}};
unsigned char code PY_index_r[][8]={
  							{"an   ",0xCF,0x12},
  							{"ang  ",0xD8,0x12},
  							{"ao   ",0xE3,0x12},
  							{"e    ",0xEA,0x12},
  							{"en   ",0xEF,0x12},
  							{"eng  ",0x04,0x13},
  							{"i    ",0x09,0x13},
  							{"ong  ",0x0C,0x13},
  							{"ou   ",0x21,0x13},
  							{"u    ",0x28,0x13},
  							{"uan  ",0x3D,0x13},
  							{"ui   ",0x42,0x13},
  							{"un   ",0x49,0x13},
  							{"uo   ",0x4E,0x13}};
unsigned char code PY_index_s[][8]={
  							{"a    ",0x53,0x13},
  							{"ai   ",0x5A,0x13},
  							{"an   ",0x63,0x13},
  							{"ang  ",0x6C,0x13},
  							{"ao   ",0x73,0x13},
  							{"e    ",0x7C,0x13},
  							{"en   ",0x83,0x13},
  							{"eng  ",0x86,0x13},
  							{"ha   ",0x89,0x13},
  							{"hai  ",0x9C,0x13},
  							{"han  ",0xA1,0x13},
  							{"hang ",0xC4,0x13},
  							{"hao  ",0xD5,0x13},
  							{"he   ",0xEC,0x13},
  							{"hen  ",0x05,0x14},
  							{"heng ",0x28,0x14},
  							{"hi   ",0x3F,0x14},
  							{"hou  ",0xA0,0x14},
  							{"hu   ",0xB5,0x14},
  							{"hua  ",0xF8,0x14},
  							{"huai ",0xFD,0x14},
  							{"huan ",0x06,0x15},
  							{"huang",0x0B,0x15},
  							{"hui  ",0x12,0x15},
  							{"hun  ",0x1B,0x15},
  							{"huo  ",0x24,0x15},
  							{"i    ",0x2D,0x15},
  							{"ong  ",0x4C,0x15},
  							{"ou   ",0x5D,0x15},
  							{"u    ",0x66,0x15},
  							{"uan  ",0x7D,0x15},
  							{"ui   ",0x84,0x15},
  							{"un   ",0x9B,0x15},
  							{"uo   ",0xA2,0x15}};
unsigned char code PY_index_t[][8]={
  							{"a    ",0xB3,0x15},
  							{"ai   ",0xC6,0x15},
  							{"an   ",0xD9,0x15},
  							{"ang  ",0xFE,0x15},
  							{"ao   ",0x19,0x16},
  							{"e    ",0x30,0x16},
  							{"eng  ",0x33,0x16},
  							{"i    ",0x3C,0x16},
  							{"ian  ",0x5B,0x16},
  							{"iao  ",0x6C,0x16},
  							{"ie   ",0x79,0x16},
  							{"ing  ",0x80,0x16},
  							{"ong  ",0x95,0x16},
  							{"ou   ",0xB0,0x16},
  							{"u    ",0xB9,0x16},
  							{"uan  ",0xD0,0x16},
  							{"ui   ",0xD5,0x16},
  							{"un   ",0xE2,0x16},
  							{"uo   ",0xEB,0x16}};
unsigned char code PY_index_w[][8]={
  							{"a    ",0x02,0x17},
  							{"ai   ",0x11,0x17},
  							{"an   ",0x16,0x17},
  							{"ang  ",0x39,0x17},
  							{"ei   ",0x4E,0x17},
  							{"en   ",0x91,0x17},
  							{"eng  ",0xA6,0x17},
  							{"o    ",0xAD,0x17},
  							{"u    ",0xC0,0x17}};
unsigned char code PY_index_x[][8]={
  							{"i    ",0xFB,0x17},
  							{"ia   ",0x40,0x18},
  							{"ian  ",0x59,0x18},
  							{"iang ",0x90,0x18},
  							{"iao  ",0xB9,0x18},
  							{"ie   ",0xDC,0x18},
  							{"in   ",0x05,0x19},
  							{"ing  ",0x1A,0x19},
  							{"iong ",0x37,0x19},
  							{"iu   ",0x46,0x19},
  							{"u    ",0x5B,0x19},
  							{"uan  ",0x82,0x19},
  							{"ue   ",0x97,0x19},
  							{"un   ",0xA6,0x19}};
unsigned char code PY_index_y[][8]={
  							{"a    ",0xC3,0x19},
  							{"an   ",0xE4,0x19},
  							{"ang  ",0x27,0x1A},
  							{"ao   ",0x4A,0x1A},
  							{"e    ",0x6D,0x1A},
  							{"i    ",0x8C,0x1A},
  							{"in   ",0xF7,0x1A},
  							{"ing  ",0x18,0x1B},
  							{"o    ",0x3D,0x1B},
  							{"ong  ",0x40,0x1B},
  							{"ou   ",0x5F,0x1B},
  							{"u    ",0x88,0x1B},
  							{"uan  ",0xE1,0x1B},
  							{"ue   ",0x0A,0x1C},
  							{"un   ",0x1D,0x1C}};
unsigned char code PY_index_z[][8]={
  							{"a    ",0x36,0x1C},
  							{"ai   ",0x3F,0x1C},
  							{"an   ",0x50,0x1C},
  							{"ang  ",0x59,0x1C},
  							{"ao   ",0x60,0x1C},
  							{"e    ",0x7D,0x1C},
  							{"ei   ",0x86,0x1C},
  							{"en   ",0x89,0x1C},
  							{"eng  ",0x8C,0x1C},
  							{"ha   ",0x93,0x1C},
  							{"hai  ",0xAE,0x1C},
  							{"han  ",0xBD,0x1C},
  							{"hang ",0xE0,0x1C},
  							{"hao  ",0x01,0x1D},
  							{"he   ",0x18,0x1D},
  							{"hen  ",0x2F,0x1D},
  							{"heng ",0x52,0x1D},
  							{"hi   ",0x6F,0x1D},
  							{"hong ",0xC6,0x1D},
  							{"hou  ",0xDD,0x1D},
  							{"hu   ",0xFA,0x1D},
  							{"hua  ",0x2F,0x1E},
  							{"huai ",0x32,0x1E},
  							{"huan ",0x35,0x1E},
  							{"huang",0x40,0x1E},
  							{"hui  ",0x51,0x1E},
  							{"hun  ",0x5E,0x1E},
  							{"huo  ",0x63,0x1E},
  							{"i    ",0x78,0x1E},
  							{"ong  ",0x95,0x1E},
  							{"ou   ",0xA4,0x1E},
  							{"u    ",0xAD,0x1E},
  							{"uan  ",0xBE,0x1E},
  							{"ui   ",0xC5,0x1E},
  							{"un   ",0xCE,0x1E},
  							{"uo   ",0xD3,0x1E}};
unsigned char code PY_index_end[][8]={"     ",0,0};
  							
//================================================================================================



//================================================================================================

//"========================================±äÁ¿ÉùÃ÷========================================"
unsigned int code py_mb_begin=(unsigned int)&PY_mb_a[0];
unsigned char code (* code PY_index_pointer[27])[8]={
											PY_index_a,PY_index_b,PY_index_c,PY_index_d,PY_index_e,PY_index_f,PY_index_g,PY_index_h,
											PY_index_j,PY_index_j,PY_index_k,PY_index_l,PY_index_m,PY_index_n,PY_index_o,PY_index_p,
											PY_index_q,PY_index_r,PY_index_s,PY_index_t,PY_index_w,PY_index_w,PY_index_w,PY_index_x,
											PY_index_y,PY_index_z,PY_index_end};

//"========================================º¯ÊıÉùÃ÷========================================"
//"Æ´ÒôÊäÈë·¨èÃÑ¯º¯Êı£¬input_pyÎªÒÑÊäÈëµÄÆ´ÒôÂë£¬·´»ØÖµÎªÖĞÎÄµÄÆğÊ¼µØÖ·£¬µ±Îª0Ê±£¬èÃÑ¯Ê§°Ü"
unsigned char code * py_ime(unsigned char input_py_val[]);

//"========================================Ö÷³ÌĞòÌå========================================"

unsigned char code * py_ime(unsigned char input_py_val[])
{
	unsigned char code (* xdata p1)[8],(* xdata p2)[8],(* xdata p3)[8];
	unsigned char xdata i=1;
	if (input_py_val[0]==0) return(0);																				//"Èç¹ûÊäÈë¿Õ×Ö·û·µ»Ø0"
	if (input_py_val[0]=='i') return(0);
	if (input_py_val[0]=='u') return(0);
	if (input_py_val[0]=='v') return(0);
	p1=p2=PY_index_pointer[input_py_val[0]-0x61];															//"¼ÆËãÈë¿ÚÊ÷¸ù"
	p3=PY_index_pointer[input_py_val[0]-0x60];																//"ÉèÖÃÖ¸Õë½çÏŞ"
	if (p1==0) return(0);																											//"²éÑ¯Ê§°Ü·µ»Ø0"
	while (p1<p3) if ((*p1)[0]==input_py_val[1]) {p2=p1;break;} else p1++;		//"²éÑ¯µÚ¶ş¸öÆ´Òô"
	p1=p2;
	while (p1<p3)																															//"½×Ìİ·¨²éÑ¯ÓàÏÂÆ´Òô"
		if (((*p1)[i]==input_py_val[i+1])&&((*p1)[i-1]==input_py_val[i])) 
		{
			p2=p1;
			i++;
		} 
		else p1++;
	return((unsigned char code *)((*p2)[6]+(*p2)[7]*256+py_mb_begin));				//"·µ»Ø²éÑ¯½á¹ûÊ×µØÖ·"
}


