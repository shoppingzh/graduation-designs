//"********************CCDC01�ɼ���������������ƴ�����뷨ģ��********************"
//"*                              ������ƣ��� ��                               *"
//"*                             ���ڣ�    2001/3                               *"
//"*                         ���뻷����Franklin 3.3.4                           *"
//"******************************************************************************"

#include <string.h>
#include <reg51.h>

//"********************CCDC01�ɼ���������������ƴ�����뷨���********************"
//"*                              ������ƣ��� ��                               *"
//"*                             ���ڣ�    2001/3                               *"
//"*                         ���뻷����Franklin 3.3.4                           *"
//"******************************************************************************"

//"ƴ�����뷨�������б�"
unsigned char code PY_mb_a     []={"����"};
unsigned char code PY_mb_ai    []={"��������������������������"};
unsigned char code PY_mb_an    []={"������������������"};
unsigned char code PY_mb_ang   []={"������"};
unsigned char code PY_mb_ao    []={"�������������°İ�"};
unsigned char code PY_mb_ba    []={"�˰ͰȰǰɰṴ̋ưʰΰϰѰаӰְհ�"};
unsigned char code PY_mb_bai   []={"�װٰ۰ذڰܰݰ�"};
unsigned char code PY_mb_ban   []={"�����߰�����������"};
unsigned char code PY_mb_bang  []={"������������������"};
unsigned char code PY_mb_bao   []={"������������������������������������"};
unsigned char code PY_mb_bei   []={"������������������������������"};
unsigned char code PY_mb_ben   []={"����������"};
unsigned char code PY_mb_beng  []={"�����±ñű�"};
unsigned char code PY_mb_bi    []={"�ƱǱȱ˱ʱɱұرϱձӱѱݱбֱԱͱױ̱αڱܱ�"};
unsigned char code PY_mb_bian  []={"�߱�ޱ���������"};
unsigned char code PY_mb_biao  []={"�����"};
unsigned char code PY_mb_bie   []={"�����"};
unsigned char code PY_mb_bin   []={"����������"};
unsigned char code PY_mb_bing  []={"������������������"};
unsigned char code PY_mb_bo    []={"����������������������������������������"};
unsigned char code PY_mb_bu    []={"��������������������"};
unsigned char code PY_mb_ca    []={"��"};
unsigned char code PY_mb_cai   []={"�²ŲĲƲòɲʲǲȲ˲�"};
unsigned char code PY_mb_can   []={"�βͲвϲѲҲ�"};
unsigned char code PY_mb_cang  []={"�ֲײԲղ�"};
unsigned char code PY_mb_cao   []={"�ٲڲܲ۲�"};
unsigned char code PY_mb_ce    []={"���޲��"};
unsigned char code PY_mb_ceng  []={"�����"};
unsigned char code PY_mb_cha   []={"�������������ɲ"};
unsigned char code PY_mb_chai  []={"����"};
unsigned char code PY_mb_chan  []={"�������������������"};
unsigned char code PY_mb_chang []={"������������������������"};
unsigned char code PY_mb_chao  []={"��������������������"};
unsigned char code PY_mb_che   []={"������������"};
unsigned char code PY_mb_chen  []={"�������������³��ĳ�"};
unsigned char code PY_mb_cheng []={"�Ƴųɳʳгϳǳ˳ͳ̳γȳѳҳ�"};
unsigned char code PY_mb_chi   []={"�Գճڳس۳ٳֳ߳޳ݳܳ����"};
unsigned char code PY_mb_chong []={"������"};
unsigned char code PY_mb_chou  []={"��������������"};
unsigned char code PY_mb_chu   []={"����������������������������������"};
unsigned char code PY_mb_chuai []={"��"};
unsigned char code PY_mb_chuan []={"��������������"};
unsigned char code PY_mb_chuang[]={"����������"};
unsigned char code PY_mb_chui  []={"����������"};
unsigned char code PY_mb_chun  []={"��������������"};
unsigned char code PY_mb_chuo  []={"��"};
unsigned char code PY_mb_ci    []={"�ôʴĴɴȴǴŴƴ˴δ̴�"};
unsigned char code PY_mb_cong  []={"�ѴӴҴдϴ�"};
unsigned char code PY_mb_cou   []={"��"};
unsigned char code PY_mb_cu    []={"�ִٴ״�"};
unsigned char code PY_mb_cuan  []={"�ڴܴ�"};
unsigned char code PY_mb_cui   []={"�޴ߴݴ�����"};
unsigned char code PY_mb_cun   []={"����"};
unsigned char code PY_mb_cuo   []={"�������"};
unsigned char code PY_mb_da    []={"�������"};
unsigned char code PY_mb_dai   []={"������������������������"};
unsigned char code PY_mb_dan   []={"������������������������������"};
unsigned char code PY_mb_dang  []={"����������"};
unsigned char code PY_mb_dao   []={"������������������������"};
unsigned char code PY_mb_de    []={"�õµ�"};
unsigned char code PY_mb_deng  []={"�Ƶǵŵȵ˵ʵ�"};
unsigned char code PY_mb_di    []={"�͵̵εҵϵеӵѵյ׵ֵصܵ۵ݵڵ޵�"};
unsigned char code PY_mb_dian  []={"���ߵ��������������"};
unsigned char code PY_mb_diao  []={"�����������"};
unsigned char code PY_mb_die   []={"��������������"};
unsigned char code PY_mb_ding  []={"������������������"};
unsigned char code PY_mb_diu   []={"��"};
unsigned char code PY_mb_dong  []={"��������������������"};
unsigned char code PY_mb_dou   []={"����������������"};
unsigned char code PY_mb_du    []={"�����������¶ĶöʶŶǶȶɶ�"};
unsigned char code PY_mb_duan  []={"�˶̶ζ϶ж�"};
unsigned char code PY_mb_dui   []={"�ѶӶԶ�"};
unsigned char code PY_mb_dun   []={"�ֶضն׶ܶ۶ٶ�"};
unsigned char code PY_mb_duo   []={"��߶�޶��������"};
unsigned char code PY_mb_e     []={"�����������������"};
unsigned char code PY_mb_en    []={"��"};
unsigned char code PY_mb_er    []={"����������������"};
unsigned char code PY_mb_fa    []={"����������������"};
unsigned char code PY_mb_fan   []={"����������������������������������"};
unsigned char code PY_mb_fang  []={"���������������·÷ķ�"};
unsigned char code PY_mb_fei   []={"�ɷǷȷƷʷ˷̷ͷϷзη�"};
unsigned char code PY_mb_fen   []={"�ַԷ׷ҷշӷطڷٷ۷ݷܷ޷߷�"};
unsigned char code PY_mb_feng  []={"�����������������"};
unsigned char code PY_mb_fo    []={"��"};
unsigned char code PY_mb_fou   []={"��"};
unsigned char code PY_mb_fu    []={"������󸥷�����������������������������������������������������������������������������"};
unsigned char code PY_mb_ga    []={"�¸�"};
unsigned char code PY_mb_gai   []={"�øĸƸǸȸ�"};
unsigned char code PY_mb_gan   []={"�ɸʸ˸θ̸͸ѸϸҸи�"};
unsigned char code PY_mb_gang  []={"�Ըոڸٸظ׸ָ۸�"};
unsigned char code PY_mb_gao   []={"�޸�߸�ݸ�����"};
unsigned char code PY_mb_ge    []={"�����������������������"};
unsigned char code PY_mb_gei   []={"��"};
unsigned char code PY_mb_gen   []={"����"};
unsigned char code PY_mb_geng  []={"��������������"};
unsigned char code PY_mb_gong  []={"������������������������������"};
unsigned char code PY_mb_gou   []={"������������������"};
unsigned char code PY_mb_gu    []={"�����ù¹��������ŹȹɹǹƹĹ̹ʹ˹�"};
unsigned char code PY_mb_gua   []={"�Ϲιйѹҹ�"};
unsigned char code PY_mb_guai  []={"�Թչ�"};
unsigned char code PY_mb_guan  []={"�ع۹ٹڹ׹ݹܹ�߹��"};
unsigned char code PY_mb_guang []={"����"};
unsigned char code PY_mb_gui   []={"�������������������"};
unsigned char code PY_mb_gun   []={"������"};
unsigned char code PY_mb_guo   []={"������������"};
unsigned char code PY_mb_ha    []={"���"};
unsigned char code PY_mb_hai   []={"��������������"};
unsigned char code PY_mb_han   []={"��������������������������������������"};
unsigned char code PY_mb_hang  []={"������"};
unsigned char code PY_mb_hao   []={"���������úºźƺ�"};
unsigned char code PY_mb_he    []={"�ǺȺ̺ϺκͺӺҺ˺ɺԺкʺغֺպ�"};
unsigned char code PY_mb_hei   []={"�ں�"};
unsigned char code PY_mb_hen   []={"�ۺܺݺ�"};
unsigned char code PY_mb_heng  []={"��ߺ���"};
unsigned char code PY_mb_hong  []={"����������"};
unsigned char code PY_mb_hou   []={"���������"};
unsigned char code PY_mb_hu    []={"������������������������������������"};
unsigned char code PY_mb_hua   []={"������������������"};
unsigned char code PY_mb_huai  []={"����������"};
unsigned char code PY_mb_huan  []={"�����������û»�������������"};
unsigned char code PY_mb_huang []={"�ĻŻʻ˻ƻ̻ͻȻǻɻлλѻ�"};
unsigned char code PY_mb_hui   []={"�һֻӻԻջػ׻ڻܻ������߻޻�ݻٻ�"};
unsigned char code PY_mb_hun   []={"�������"};
unsigned char code PY_mb_huo   []={"��������������"};
unsigned char code PY_mb_ji    []={"���������������������������������������������������������������������ƼǼ��ͼ˼ɼ��ʼ����ȼü̼żļ¼�������"};
unsigned char code PY_mb_jia   []={"�ӼмѼϼҼμԼռ׼ּؼۼݼܼټ޼�Ю"};
unsigned char code PY_mb_jian  []={"����߼�����������������������������������������������������"};
unsigned char code PY_mb_jiang []={"��������������������������"};
unsigned char code PY_mb_jiao  []={"���������������������ǽƽʽȽýŽ½��˽ɽнνϽ̽ѽ;���"};
unsigned char code PY_mb_jie   []={"�׽Խӽսҽֽڽٽܽ��ݽ޽ؽ߽����������"};
unsigned char code PY_mb_jin   []={"����������������������������������"};
unsigned char code PY_mb_jing  []={"��������������������������������������������������"};
unsigned char code PY_mb_jiong []={"����"};
unsigned char code PY_mb_jiu   []={"�������žþľ��¾ƾɾʾ̾ξǾȾ;�"};
unsigned char code PY_mb_ju    []={"�ӾоѾԾҾϾֽ۾վ׾ھپؾ�޾ܾ߾����ݾ��۾�"};
unsigned char code PY_mb_juan  []={"���������"};
unsigned char code PY_mb_jue   []={"��������������"};
unsigned char code PY_mb_jun   []={"����������������������"};
unsigned char code PY_mb_ka    []={"������"};
unsigned char code PY_mb_kai   []={"����������"};
unsigned char code PY_mb_kan   []={"��������������"};
unsigned char code PY_mb_kang  []={"��������������"};
unsigned char code PY_mb_kao   []={"��������"};
unsigned char code PY_mb_ke    []={"�����¿ƿÿſĿǿȿɿʿ˿̿Ϳ�"};
unsigned char code PY_mb_ken   []={"�Ͽѿҿ�"};
unsigned char code PY_mb_keng  []={"�Կ�"};
unsigned char code PY_mb_kong  []={"�տ׿ֿ�"};
unsigned char code PY_mb_kou   []={"�ٿڿۿ�"};
unsigned char code PY_mb_ku    []={"�ݿ޿߿����"};
unsigned char code PY_mb_kua   []={"������"};
unsigned char code PY_mb_kuai  []={"�����"};
unsigned char code PY_mb_kuan  []={"����"};
unsigned char code PY_mb_kuang []={"�����������"};
unsigned char code PY_mb_kui   []={"����������������������"};
unsigned char code PY_mb_kun   []={"��������"};
unsigned char code PY_mb_kuo   []={"��������"};
unsigned char code PY_mb_la    []={"��������������"};
unsigned char code PY_mb_lai   []={"������"};
unsigned char code PY_mb_lan   []={"������������������������������"};
unsigned char code PY_mb_lang  []={"��������������"};
unsigned char code PY_mb_lao   []={"������������������"};
unsigned char code PY_mb_le    []={"������"};
unsigned char code PY_mb_lei   []={"����������������������"};
unsigned char code PY_mb_leng  []={"������"};
unsigned char code PY_mb_li    []={"��������������������������������������������������������������������"};
unsigned char code PY_mb_lian  []={"����������������������������"};
unsigned char code PY_mb_liang []={"������������������������"};
unsigned char code PY_mb_liao  []={"������������������������"};
unsigned char code PY_mb_lie   []={"����������"};
unsigned char code PY_mb_lin   []={"������������������������"};
unsigned char code PY_mb_ling  []={"����������������������������"};
unsigned char code PY_mb_liu   []={"����������������������"};
unsigned char code PY_mb_long  []={"��������¡��¤¢£"};
unsigned char code PY_mb_lou   []={"¦¥§¨ª©"};
unsigned char code PY_mb_lu    []={"¶¬®«¯­±²°³½¼¸¹»µ·¾º´"};
unsigned char code PY_mb_luan  []={"������������"};
unsigned char code PY_mb_lue   []={"����"};
unsigned char code PY_mb_lun   []={"��������������"};
unsigned char code PY_mb_luo   []={"������������������������"};
unsigned char code PY_mb_lv    []={"��¿������������������������"};
unsigned char code PY_mb_ma    []={"������������������"};
unsigned char code PY_mb_mai   []={"������������"};
unsigned char code PY_mb_man   []={"����������á������"};
unsigned char code PY_mb_mang  []={"æâäãçå"};
unsigned char code PY_mb_mao   []={"èëìéêîíïðóñò"};
unsigned char code PY_mb_me    []={"ô"};
unsigned char code PY_mb_mei   []={"ûöõü÷ýúøùÿ��þ��������"};
unsigned char code PY_mb_men   []={"������"};
unsigned char code PY_mb_meng  []={"����������������"};
unsigned char code PY_mb_mi    []={"����������������������������"};
unsigned char code PY_mb_mian  []={"������������������"};
unsigned char code PY_mb_miao  []={"����������������"};
unsigned char code PY_mb_mie   []={"����"};
unsigned char code PY_mb_min   []={"������������"};
unsigned char code PY_mb_ming  []={"������������"};
unsigned char code PY_mb_miu   []={"��"};
unsigned char code PY_mb_mo    []={"����ġģĤĦĥĢħĨĩĭİĪįĮīĬ"};
unsigned char code PY_mb_mou   []={"Ĳıĳ"};
unsigned char code PY_mb_mu    []={"ĸĶĵķĴľĿ��ļĹĻ��Ľĺ��"};
unsigned char code PY_mb_na    []={"��������������"};
unsigned char code PY_mb_nai   []={"����������"};
unsigned char code PY_mb_nan   []={"������"};
unsigned char code PY_mb_nang  []={"��"};
unsigned char code PY_mb_nao   []={"����������"};
unsigned char code PY_mb_ne    []={"��"};
unsigned char code PY_mb_nei   []={"����"};
unsigned char code PY_mb_nen   []={"��"};
unsigned char code PY_mb_neng  []={"��"};
unsigned char code PY_mb_ni    []={"����������������������"};
unsigned char code PY_mb_nian  []={"��������������"};
unsigned char code PY_mb_niang []={"����"};
unsigned char code PY_mb_niao  []={"����"};
unsigned char code PY_mb_nie   []={"��������������"};
unsigned char code PY_mb_nin   []={"��"};
unsigned char code PY_mb_ning  []={"��š������Ţ"};
unsigned char code PY_mb_niu   []={"ţŤŦť"};
unsigned char code PY_mb_nong  []={"ũŨŧŪ"};
unsigned char code PY_mb_nu    []={"ūŬŭ"};
unsigned char code PY_mb_nuan  []={"ů"};
unsigned char code PY_mb_nue   []={"űŰ"};
unsigned char code PY_mb_nuo   []={"ŲŵųŴ"};
unsigned char code PY_mb_nv    []={"Ů"};
unsigned char code PY_mb_o     []={"Ŷ"};
unsigned char code PY_mb_ou    []={"ŷŹŸŻżźŽ"};
unsigned char code PY_mb_pa    []={"ſž����������"};
unsigned char code PY_mb_pai   []={"������������"};
unsigned char code PY_mb_pan   []={"����������������"};
unsigned char code PY_mb_pang  []={"����������"};
unsigned char code PY_mb_pao   []={"��������������"};
unsigned char code PY_mb_pei   []={"������������������"};
unsigned char code PY_mb_pen   []={"����"};
unsigned char code PY_mb_peng  []={"����������������������������"};
unsigned char code PY_mb_pi    []={"��������������Ƥ��ƣơ��ƢƥƦƨƧƩ"};
unsigned char code PY_mb_pian  []={"Ƭƫƪƭ"};
unsigned char code PY_mb_piao  []={"ƯƮưƱ"};
unsigned char code PY_mb_pie   []={"ƲƳ"};
unsigned char code PY_mb_pin   []={"ƴƶƵƷƸ"};
unsigned char code PY_mb_ping  []={"ƹƽ��ƾƺƻ��ƿƼ"};
unsigned char code PY_mb_po    []={"����������������"};
unsigned char code PY_mb_pou   []={"��"};
unsigned char code PY_mb_pu    []={"������������������������������"};
unsigned char code PY_mb_qi    []={"������������������������������������������������������������������������"};
unsigned char code PY_mb_qia   []={"��ǡǢ"};
unsigned char code PY_mb_qian  []={"ǧǪǤǨǥǣǦǫǩǰǮǯǬǱǭǳǲǴǷǵǶǸ"};
unsigned char code PY_mb_qiang []={"ǺǼǹǻǿǽǾ��"};
unsigned char code PY_mb_qiao  []={"������������������������������"};
unsigned char code PY_mb_qie   []={"����������"};
unsigned char code PY_mb_qin   []={"����������������������"};
unsigned char code PY_mb_qing  []={"��������������������������"};
unsigned char code PY_mb_qiong []={"����"};
unsigned char code PY_mb_qiu   []={"����������������"};
unsigned char code PY_mb_qu    []={"����������������ȡȢȣȥȤ"};
unsigned char code PY_mb_quan  []={"ȦȫȨȪȭȬȩȧȮȰȯ"};
unsigned char code PY_mb_que   []={"Ȳȱȳȴȸȷȵȶ"};
unsigned char code PY_mb_qun   []={"ȹȺ"};
unsigned char code PY_mb_ran   []={"ȻȼȽȾ"};
unsigned char code PY_mb_rang  []={"ȿ��������"};
unsigned char code PY_mb_rao   []={"������"};
unsigned char code PY_mb_re    []={"����"};
unsigned char code PY_mb_ren   []={"��������������������"};
unsigned char code PY_mb_reng  []={"����"};
unsigned char code PY_mb_ri    []={"��"};
unsigned char code PY_mb_rong  []={"��������������������"};
unsigned char code PY_mb_rou   []={"������"};
unsigned char code PY_mb_ru    []={"��������������������"};
unsigned char code PY_mb_ruan  []={"����"};
unsigned char code PY_mb_rui   []={"������"};
unsigned char code PY_mb_run   []={"����"};
unsigned char code PY_mb_ruo   []={"����"};
unsigned char code PY_mb_sa    []={"������"};
unsigned char code PY_mb_sai   []={"��������"};
unsigned char code PY_mb_san   []={"����ɡɢ"};
unsigned char code PY_mb_sang  []={"ɣɤɥ"};
unsigned char code PY_mb_sao   []={"ɦɧɨɩ"};
unsigned char code PY_mb_se    []={"ɫɬɪ"};
unsigned char code PY_mb_sen   []={"ɭ"};
unsigned char code PY_mb_seng  []={"ɮ"};
unsigned char code PY_mb_sha   []={"ɱɳɴɰɯɵɶɷ��"};
unsigned char code PY_mb_shai  []={"ɸɹ"};
unsigned char code PY_mb_shan  []={"ɽɾɼ��ɺɿ������ɻ������������դ"};
unsigned char code PY_mb_shang []={"����������������"};
unsigned char code PY_mb_shao  []={"����������������������"};
unsigned char code PY_mb_she   []={"������������������������"};
unsigned char code PY_mb_shen  []={"��������������������������������ʲ"};
unsigned char code PY_mb_sheng []={"��������ʤ����ʡʥʢʣ"};
unsigned char code PY_mb_shi   []={"��ʬʧʦʭʫʩʨʪʮʯʱʶʵʰʴʳʷʸʹʼʻʺʿ��������ʾʽ������������������������������������"};
unsigned char code PY_mb_shou  []={"��������������������"};
unsigned char code PY_mb_shu   []={"������������������������������������������������������ˡ����������"};
unsigned char code PY_mb_shua  []={"ˢˣ"};
unsigned char code PY_mb_shuai []={"˥ˤ˦˧"};
unsigned char code PY_mb_shuan []={"˩˨"};
unsigned char code PY_mb_shuang[]={"˫˪ˬ"};
unsigned char code PY_mb_shui  []={"˭ˮ˰˯"};
unsigned char code PY_mb_shun  []={"˱˳˴˲"};
unsigned char code PY_mb_shuo  []={"˵˸˷˶"};
unsigned char code PY_mb_si    []={"˿˾˽˼˹˻˺����������������"};
unsigned char code PY_mb_song  []={"����������������"};
unsigned char code PY_mb_sou   []={"��������"};
unsigned char code PY_mb_su    []={"����������������������"};
unsigned char code PY_mb_suan  []={"������"};
unsigned char code PY_mb_sui   []={"����������������������"};
unsigned char code PY_mb_sun   []={"������"};
unsigned char code PY_mb_suo   []={"����������������"};
unsigned char code PY_mb_ta    []={"����������̡̢̤̣"};
unsigned char code PY_mb_tai   []={"̨̧̥̦̫̭̬̩̪"};
unsigned char code PY_mb_tan   []={"̸̵̷̶̴̮̰̯̲̱̳̹̻̺̼̾̿̽"};
unsigned char code PY_mb_tang  []={"��������������������������"};
unsigned char code PY_mb_tao   []={"����������������������"};
unsigned char code PY_mb_te    []={"��"};
unsigned char code PY_mb_teng  []={"��������"};
unsigned char code PY_mb_ti    []={"������������������������������"};
unsigned char code PY_mb_tian  []={"����������������"};
unsigned char code PY_mb_tiao  []={"������������"};
unsigned char code PY_mb_tie   []={"������"};
unsigned char code PY_mb_ting  []={"��͡����ͤͥͣͦͧ͢"};
unsigned char code PY_mb_tong  []={"ͨͬͮͩͭͯͪͫͳͱͰͲʹ"};
unsigned char code PY_mb_tou   []={"͵ͷͶ͸"};
unsigned char code PY_mb_tu    []={"͹ͺͻͼͽͿ;��������"};
unsigned char code PY_mb_tuan  []={"����"};
unsigned char code PY_mb_tui   []={"������������"};
unsigned char code PY_mb_tun   []={"��������"};
unsigned char code PY_mb_tuo   []={"����������������������"};
unsigned char code PY_mb_wa    []={"��������������"};
unsigned char code PY_mb_wai   []={"����"};
unsigned char code PY_mb_wan   []={"����������������������������������"};
unsigned char code PY_mb_wang  []={"��������������������"};
unsigned char code PY_mb_wei   []={"Σ��΢ΡΪΤΧΥΦΨΩάΫΰαβγέίή��δλζηθξνιμεοκ"};
unsigned char code PY_mb_wen   []={"��������������������"};
unsigned char code PY_mb_weng  []={"������"};
unsigned char code PY_mb_wo    []={"������������������"};
unsigned char code PY_mb_wu    []={"����������������������������������������������������������"};
unsigned char code PY_mb_xi    []={"Ϧϫ����ϣ������Ϣ��Ϥϧϩ����ϬϡϪ��Ϩ����ϥϰϯϮϱϭϴϲϷϵϸ϶"};
unsigned char code PY_mb_xia   []={"ϺϹϻ��Ͽ��ϾϽϼ������"};
unsigned char code PY_mb_xian  []={"ϳ����������������������������������������������������"};
unsigned char code PY_mb_xiang []={"����������������������������������������"};
unsigned char code PY_mb_xiao  []={"����������������С��ТФ��ЧУЦХ"};
unsigned char code PY_mb_xie   []={"ЩШЪЫЭавбгЯЬдйкжмелиз"};
unsigned char code PY_mb_xin   []={"����о����п��н����"};
unsigned char code PY_mb_xing  []={"����������������������������"};
unsigned char code PY_mb_xiong []={"��������������"};
unsigned char code PY_mb_xiu   []={"��������������������"};
unsigned char code PY_mb_xu    []={"��������������������������������������"};
unsigned char code PY_mb_xuan  []={"������������ѡѢѤѣ"};
unsigned char code PY_mb_xue   []={"��ѥѦѨѧѩѪ"};
unsigned char code PY_mb_xun   []={"ѫѬѰѲѮѱѯѭѵѶѴѸѷѳ"};
unsigned char code PY_mb_ya    []={"ѾѹѽѺѻѼ��ѿ����������������"};
unsigned char code PY_mb_yan   []={"������������������������������������������������������������������"};
unsigned char code PY_mb_yang  []={"����������������������������������"};
unsigned char code PY_mb_yao   []={"��������ҢҦҤҥҡң��ҧҨҩҪҫԿ"};
unsigned char code PY_mb_ye    []={"ҬҭүҮҲұҰҵҶҷҳҹҴҺҸ"};
unsigned char code PY_mb_yi    []={"һ����ҽ��ҿҼҾ������������������������������������������������������������������������������������������"};
unsigned char code PY_mb_yin   []={"������������������������������ӡ"};
unsigned char code PY_mb_ying  []={"ӦӢӤӧӣӥӭӯӫӨөӪӬӮӱӰӳӲ"};
unsigned char code PY_mb_yo    []={"Ӵ"};
unsigned char code PY_mb_yong  []={"ӶӵӸӹӺӷ��ӽӾ��ӿ��Ӽӻ��"};
unsigned char code PY_mb_you   []={"����������������������������������������"};
unsigned char code PY_mb_yu    []={"����������������������������������������������������Ԧ����������ԡԤ������Ԣ��ԣ������ԥ"};
unsigned char code PY_mb_yuan  []={"ԩԧԨԪԱ԰ԫԭԲԬԮԵԴԳԯԶԷԹԺԸ"};
unsigned char code PY_mb_yue   []={"ԻԼ��������Ծ��Խ"};
unsigned char code PY_mb_yun   []={"������������������������"};
unsigned char code PY_mb_za    []={"������զ"};
unsigned char code PY_mb_zai   []={"����������������"};
unsigned char code PY_mb_zan   []={"��������"};
unsigned char code PY_mb_zang  []={"������"};
unsigned char code PY_mb_zao   []={"����������������������������"};
unsigned char code PY_mb_ze    []={"��������"};
unsigned char code PY_mb_zei   []={"��"};
unsigned char code PY_mb_zen   []={"��"};
unsigned char code PY_mb_zeng  []={"������"};
unsigned char code PY_mb_zha   []={"����������բագէթըե��"};
unsigned char code PY_mb_zhai  []={"իժլ��խծկ"};
unsigned char code PY_mb_zhan  []={"մձճղհնչյոշռսջվ��տպ"};
unsigned char code PY_mb_zhang []={"��������������������������������"};
unsigned char code PY_mb_zhao  []={"��������������������צ"};
unsigned char code PY_mb_zhe   []={"����������������������"};
unsigned char code PY_mb_zhen  []={"��������������������������������֡"};
unsigned char code PY_mb_zheng []={"��������������������֤֣��֢"};
unsigned char code PY_mb_zhi   []={"ְֱֲֳִֵֶַָֹֺֻּֽ֧֥֦֪֭֮֨֯֫֬֩��־������������ֿ������������������"};
unsigned char code PY_mb_zhong []={"����������������������"};
unsigned char code PY_mb_zhou  []={"����������������������������"};
unsigned char code PY_mb_zhu   []={"������������������������������ס��ע��פ��ף��������"};
unsigned char code PY_mb_zhua  []={"ץ"};
unsigned char code PY_mb_zhuai []={"ק"};
unsigned char code PY_mb_zhuan []={"רשת׫׭"};
unsigned char code PY_mb_zhuang[]={"ױׯ׮װ׳״��ײ"};
unsigned char code PY_mb_zhui  []={"׷׵׶׹׺׸"};
unsigned char code PY_mb_zhun  []={"׻׼"};
unsigned char code PY_mb_zhuo  []={"׿׾׽��������������"};
unsigned char code PY_mb_zi    []={"����������������������������"};
unsigned char code PY_mb_zong  []={"��������������"};
unsigned char code PY_mb_zou   []={"��������"};
unsigned char code PY_mb_zu    []={"����������������"};
unsigned char code PY_mb_zuan  []={"׬����"};
unsigned char code PY_mb_zui   []={"��������"};
unsigned char code PY_mb_zun   []={"����"};
unsigned char code PY_mb_zuo   []={"��������������"};

//================================================================================================


//"ƴ�����뷨��ѯ���"

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

//"========================================��������========================================"
unsigned int code py_mb_begin=(unsigned int)&PY_mb_a[0];
unsigned char code (* code PY_index_pointer[27])[8]={
											PY_index_a,PY_index_b,PY_index_c,PY_index_d,PY_index_e,PY_index_f,PY_index_g,PY_index_h,
											PY_index_j,PY_index_j,PY_index_k,PY_index_l,PY_index_m,PY_index_n,PY_index_o,PY_index_p,
											PY_index_q,PY_index_r,PY_index_s,PY_index_t,PY_index_w,PY_index_w,PY_index_w,PY_index_x,
											PY_index_y,PY_index_z,PY_index_end};

//"========================================��������========================================"
//"ƴ�����뷨��ѯ������input_pyΪ�������ƴ���룬����ֵΪ���ĵ���ʼ��ַ����Ϊ0ʱ����ѯʧ��"
unsigned char code * py_ime(unsigned char input_py_val[]);

//"========================================��������========================================"

unsigned char code * py_ime(unsigned char input_py_val[])
{
	unsigned char code (* xdata p1)[8],(* xdata p2)[8],(* xdata p3)[8];
	unsigned char xdata i=1;
	if (input_py_val[0]==0) return(0);																				//"���������ַ�����0"
	if (input_py_val[0]=='i') return(0);
	if (input_py_val[0]=='u') return(0);
	if (input_py_val[0]=='v') return(0);
	p1=p2=PY_index_pointer[input_py_val[0]-0x61];															//"�����������"
	p3=PY_index_pointer[input_py_val[0]-0x60];																//"����ָ�����"
	if (p1==0) return(0);																											//"��ѯʧ�ܷ���0"
	while (p1<p3) if ((*p1)[0]==input_py_val[1]) {p2=p1;break;} else p1++;		//"��ѯ�ڶ���ƴ��"
	p1=p2;
	while (p1<p3)																															//"���ݷ���ѯ����ƴ��"
		if (((*p1)[i]==input_py_val[i+1])&&((*p1)[i-1]==input_py_val[i])) 
		{
			p2=p1;
			i++;
		} 
		else p1++;
	return((unsigned char code *)((*p2)[6]+(*p2)[7]*256+py_mb_begin));				//"���ز�ѯ����׵�ַ"
}


