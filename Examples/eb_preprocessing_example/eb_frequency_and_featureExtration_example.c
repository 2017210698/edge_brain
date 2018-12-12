/****************************************************************************
 * Copyright (C) 2017-2018 PI2STAR                                          *
 ****************************************************************************/

/**
 * @file eb_preprocessing_example.c
 * @author Winfred SU
 * @date 28 Nov 2018
 * @brief Examples of preprocessing functions
 *
 * Demonstrates the use of the preprocessing functions. 
 */

#include "arm_math.h"
#include "edge_brain.h"

#define srcLen 400 // test data length
#define pitch 70 // base frequency
#define halfBand 20 // bandwidth 
#define dstSize 5 // Maximum order of harmonics
#define samplingRate 1024 // sampling rate
uint16_t fftSize=1024; // real sequence fft length
uint8_t ifftFlag=0; // rfft if flag is 0, rifft if flag is 1

int main(void)
{
	// ------------------------------------------------------------------
  /* test input data */
	float32_t testSrc[srcLen]={1.0,0.9729576772107981,0.8431911938133144,0.6168586556450661,0.31165687052447905,-0.04395215056310799,-0.4129616910585193,-0.7534136495964521,-1.0230893429673524,-1.184824737153055,-1.2118132430692898,-1.0921607201744294,-0.8319515979233209,-0.4561901407496391,-0.00720056846018529,0.45961029675365195,0.882337585518377,1.200817789970451,1.365476498211295,1.3454985819354386,1.134969814666546,0.755787650084851,0.256510654710783,-0.2931180843879978,-0.8115471766875206,-1.2175532689885695,-1.4433874216132943,-1.446799395669225,-1.219757892233369,-0.7920244389599389,-0.22845950887870467,0.3800417002323398,0.930923817795526,1.327495596820333,1.4966284917761863,1.4033233859896908,1.0591209595409492,0.5222449794892596,-0.11119526906254391,-0.7238909738726892,-1.1991667438859794,-1.4439283245385606,-1.4081213813565645,-1.0964488560978685,-0.5693923751553828,0.06735714468629553,0.683512596015782,1.1509870505516167,1.3713675843590212,1.2980268974523446,0.9476406541469463,0.39796244925707647,-0.22831021293150622,-0.7905021465934156,-1.1619399612214747,-1.2595978651447295,-1.0642256726368715,-0.6257215185667392,-0.05188821720932143,0.5172352118791635,0.9435404382493331,1.125164132922446,1.0222091076656068,0.6670132322261269,0.15589971269371813,-0.3758617964953212,-0.7896029165386267,-0.9799923995323212,-0.9030348659212174,-0.5875336103360204,-0.12661014264906556,0.3486152776817311,0.7059803937278741,0.849485525539819,0.746087757954469,0.4342680073887964,0.011774704154670234,-0.39393390554021807,-0.6638267346377046,-0.7226189674982771,-0.5606154350877677,-0.2354363724516186,0.14688710899244203,0.4655798827070649,0.6230468468372047,0.5751520158867288,0.34429819505432846,0.011165928412589066,-0.3122277529402262,-0.5194595783500879,-0.544625929904669,-0.3838149647566473,-0.09596242223182483,0.21736088239978033,0.4466866368565236,0.5123783087385182,0.39253987992267936,0.13127655877742375,-0.17609684853709331,-0.4164424921712423,-0.4996125837088884,-0.39233068405673616,-0.1324648507175358,0.1826408435021409,0.4309675539997211,0.5120601009394428,0.38769261243004327,0.10061607700541204,-0.2378540311442777,-0.4890868132566597,-0.5429182350867383,-0.3661108573349416,-0.022287940241537626,0.3480894825767537,0.5831228176344322,0.5695362658855518,0.29761993126171793,-0.12550752671118096,-0.5149986382534508,-0.6873682314837459,-0.5468190127102047,-0.13852320308881164,0.36047397507726275,0.7152633881822473,0.7428379405912618,0.40708303888289843,-0.15024498632585245,-0.6652082235797291,-0.8749765703490717,-0.6524344934411309,-0.08335080371313938,0.5603404383787961,0.9477543543234006,0.8592239358757651,0.31234865346382484,-0.4286644149631061,-0.9768223169790741,-1.02403152481883,-0.5163032466952645,0.2976988109566206,0.9835481964227701,1.1519771393515112,0.6821813541952172,-0.1913196431578842,-0.9899292950143294,-1.2518682813932898,-0.8018668377647217,0.12878000004571125,1.0146274759848737,1.3312197921386202,0.8686859226441348,-0.12493757600786029,-1.0699957072381685,-1.3919417001872112,-0.8743492483258886,0.1903466704849773,1.1594840385933636,1.427131893314514,0.8075217168336906,-0.3299779426078967,-1.274930606539735,-1.4194857061938737,-0.6550845792545864,0.53981748131086,1.3939276833768017,1.3422919528457116,0.4069516380047571,-0.8015122007428332,-1.4785687757443535,-1.1644841648681181,-0.0646709459087717,1.0766834728574068,1.4781049065504397,0.8611373109187332,-0.3474876863377524,-1.30442195304637,-1.3386604678220457,-0.4293397159321888,0.7728862490867933,1.4070839392352812,1.0220239676197491,-0.09406445185840598,-1.121284837201818,-1.3092287039905521,-0.5314317362145504,0.6213062037799144,1.2843418971277127,0.9702481659756049,-0.06486199743433609,-1.0214221950018632,-1.1724832936043383,-0.4218945201481642,0.6287745824148877,1.1571986363499545,0.7664633274481242,-0.20977115829400528,-0.9838818180307761,-0.9489493654951423,-0.1601301415208102,0.7240463032392777,0.9876266784226828,0.4402121704784018,-0.4409639959619644,-0.9207391936440981,-0.6200992542099711,0.179560053532267,0.790991204951426,0.7101159345609711,0.035323272293579185,-0.6355003261070615,-0.7311212205896548,-0.19556003470343838,0.481233891424686,0.7064930489656639,0.3043579270575498,-0.34452113168714654,-0.6571320298502363,-0.37099464487821077,0.23289118751580795,0.599198680658504,0.4067524731387352,-0.14777806269563862,-0.5437904713271601,-0.4223196177507593,0.08715152078401492,0.4977086347759534,0.42645359035940145,-0.04761980173925467,-0.46463723082670844,-0.42551337203308315,0.02589315499981261,0.4462903987857066,0.4234613691358968,-0.01968150801547676,-0.44328393172272923,-0.4220204355966442,0.02815724833876589,0.4556207780733256,0.4207844429913967,-0.05208917995975868,-0.4827518875479765,-0.4171948331711638,0.09368522953252346,0.5232088212961206,0.40640546597833854,-0.15610029335180894,-0.5738354598242448,-0.3811696010891715,0.24249939099779502,0.6287065005476687,0.33199883826861754,-0.3545468000712748,-0.6779380456095386,-0.2479507542333493,0.4902593836434479,0.7067818710561452,0.11845784198635398,-0.6413614505209756,-0.6956274803096637,0.06346150681845125,0.7906390460236794,0.6217359350678149,-0.2965712964791301,-0.9102910179776987,-0.46354424086128293,0.565950009895378,0.9627854214190531,0.20799188047609898,-0.8382183726282194,-0.9059751536365928,0.13968341011534366,1.060071502633937,0.7037826577080449,-0.5459212561581145,-1.1634352294932202,-0.34217985379522053,0.9428927138143147,1.080112460839107,-0.15272421280612078,-1.2325004358832272,-0.7662888263671352,0.7014168503399283,1.3057729894050172,0.23232795152368613,-1.1724405262109816,-1.0790861441493107,0.43319147460082785,1.4080262914037205,0.5403567422526907,-1.0613584306977757,-1.2766596664317607,0.21242652635671755,1.4379374276275896,0.7415378069327379,-0.9659227546013489,-1.3791326065112466,0.08331603094697922,1.442071331779793,0.8290557811971314,-0.9284131780272479,-1.4068265726582638,0.06609289797569712,1.4462864850250885,0.8028555706820335,-0.9641728735160454,-1.365666837944476,0.16398661525700273,1.449162733624586,0.6614459078867323,-1.0616314715375204,-1.2432193800580722,0.36413287090488766,1.4219100507735318,0.4047176579074535,-1.1815379947088365,-1.0154483360283797,0.6313983733765669,1.3150984756286714,0.04713726641865634,-1.2581997069974187,-0.6645109471904004,0.9001506510691593,1.0759272026935525,-0.36371754141808493,-1.21060300500617,-0.2053345203414861,1.074905035117495,0.6785778584405229,-0.7350721578811378,-0.9715212687068908,0.28929978407960877,1.0532192765418333,0.16094470919851495,-0.9410545670714962,-0.5331570471932102,0.6860206790543989,0.7761203190342255,-0.35460101226829704,-0.8723248131377587,0.012302303194475731,0.8328385361361461,0.28805963282647956,-0.6879832298033838,-0.5122865539173874,0.4770345929546644,0.6455140006002027,-0.2393260820771303,-0.6892221973254096,0.008046164037176283,0.6563148205616831,0.19297388742979243,-0.5658247493688389,-0.34988785810217804,0.43833624076004757,0.4576476827121936,-0.29268752567449435,-0.5178428175625767,0.14407184221139246,0.5362824233880147,-0.003352760998882866,-0.5208181192272063,-0.1227415591673795,0.4796739481260883,0.23090919777305932,-0.4203583371146932,-0.32036339884048626,0.34910265387149897,0.3919439780960051,-0.27070297015258654,-0.44738172934105236,0.1886235318726919,0.4887672677579381,-0.10523509182144637,-0.5182201576913421,0.022092336453852605,0.5377225311109526,0.05981046069863974,-0.5490693764250457,-0.13983564924001507,0.5538890703754998,0.21755747563904454,-0.5536964979052988,-0.2926692964208597,0.5499524603159617,0.36492867313151667,-0.5441138180189296,-0.43412476119556004,0.5376672482454993,0.500054215243175,-0.5321450620286916,-0.5624952667065213,0.5291244016390151,0.6211734807518794,-0.5302118992039135,-0.675716276009461,0.5370152171353532,0.7255963166659674,-0.5511014799653899,-0.7700663750839551,0.5739410137850285};
	float32_t testDst[dstSize]; // store harmonic wave magnitude
	float32_t testEnvolop[srcLen];
	/* pFftBuffer and pMagBuffer store intermediate data */
	float32_t pFftBuffer[srcLen];
	float32_t pMagBuffer[srcLen];
	
	eb_harmonic_freq_f32(testSrc,testDst,pFftBuffer,pMagBuffer,pitch,halfBand,dstSize,samplingRate);
		
	eb_envolop_spectrum_f32(testSrc,testEnvolop,pFftBuffer,srcLen,fftSize);
		
	while(1);
}
