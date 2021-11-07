#include "Properties.h"
namespace WMFConverter{

		Properties::Properties(){};

		string Properties::findVal(string val){
			map<string, string>::iterator iter = dictMap.find(val);
			if (iter != dictMap.end())
			{
				//return iter->second;
				return "";
			}
			else
			{
				return "";
			}
		}

		void Properties::load(){



			//dictMap.insert(pair<string,string>("alternative-font.\uff2d\uff33\u0020\u30b4\u30b7\u30c3\u30af", "MS Gothic"));
			//dictMap.insert(pair<string,string>("alternative-font.\uff2d\uff33\u0020\uff30\u30b4\u30b7\u30c3\u30af", "MS PGothic"));
			//dictMap.insert(pair<string,string>("alternative-font.\uff2d\uff33\u0020\u660e\u671d", "MS Mincho"));
			//dictMap.insert(pair<string,string>("alternative-font.\uff2d\uff33\u0020\uff30\u660e\u671d", "MS PMincho"));
			//dictMap.insert(pair<string,string>("alternative-font.\u30E1\u30A4\u30EA\u30AA", "Meiryo"));

			dictMap.insert(pair<string,string>("font-emheight.Andalus", "0.655150351887396"));
			//dictMap.insert(pair<string,string>("font-emheight.Angsana\u0020New", "0.740285559371046"));
			dictMap.insert(pair<string,string>("font-emheight.AngsanaUPC", "0.740285559371046"));
			dictMap.insert(pair<string,string>("font-emheight.Aparajita", "0.846280991735537"));
			//dictMap.insert(pair<string,string>("font-emheight.Arabic\u0020Typesetting", "0.877463581833762"));
			dictMap.insert(pair<string,string>("font-emheight.Arial", "0.895104895104895"));
			//dictMap.insert(pair<string,string>("font-emheight.Arial\u0020Black", "0.709141274238227"));
			//dictMap.insert(pair<string,string>("font-emheight.Browallia\u0020New", "0.800312622118015"));
			dictMap.insert(pair<string,string>("font-emheight.BrowalliaUPC", "0.800312622118015"));
			dictMap.insert(pair<string,string>("font-emheight.Calibri", "0.8192"));
			dictMap.insert(pair<string,string>("font-emheight.Cambria", "0.852977925864223"));
			//dictMap.insert(pair<string,string>("font-emheight.Cambria\u0020Math", "0.179208960448022"));
			//dictMap.insert(pair<string,string>("font-emheight.Comic\u0020Sans\u0020MS", "0.717589348283111"));
			dictMap.insert(pair<string,string>("font-emheight.Consolas", "0.854045037531276"));
			dictMap.insert(pair<string,string>("font-emheight.Constantia", "0.8192"));
			dictMap.insert(pair<string,string>("font-emheight.Corbel", "0.8192"));
			//dictMap.insert(pair<string,string>("font-emheight.Cordia\u0020New", "0.721380767876013"));
			dictMap.insert(pair<string,string>("font-emheight.CordiaUPC", "0.721380767876013"));
			//dictMap.insert(pair<string,string>("font-emheight.Courier\u0020New", "0.882758620689655"));
			dictMap.insert(pair<string,string>("font-emheight.DaunPenh", "0.745540589734256"));
			dictMap.insert(pair<string,string>("font-emheight.David", "1.01637717121588"));
			//dictMap.insert(pair<string,string>("font-emheight.DejaVu\u0020Sans", "0.859060402684564"));
			//dictMap.insert(pair<string,string>("font-emheight.DejaVu\u0020Sans\u0020Mono", "0.859060402684564"));
			//dictMap.insert(pair<string,string>("font-emheight.DejaVu\u0020Serif", "0.859060402684564"));
			dictMap.insert(pair<string,string>("font-emheight.DilleniaUPC", "0.766323666978485"));
			dictMap.insert(pair<string,string>("font-emheight.DokChampa", "0.516259137887572"));
			//dictMap.insert(pair<string,string>("font-emheight.Dutch801\u0020SWC", "0.844187963726298"));
			dictMap.insert(pair<string,string>("font-emheight.Ebrima", "0.751835535976505"));
			//dictMap.insert(pair<string,string>("font-emheight.Estrangelo\u0020Edessa", "0.894323144104804"));
			dictMap.insert(pair<string,string>("font-emheight.EucrosiaUPC", "0.816912644595134"));
			dictMap.insert(pair<string,string>("font-emheight.Euphemia", "0.761338289962825"));
			//dictMap.insert(pair<string,string>("font-emheight.Franklin\u0020Gothic\u0020Medium", "0.881998277347115"));
			dictMap.insert(pair<string,string>("font-emheight.FrankRuehl", "1.07563025210084"));
			dictMap.insert(pair<string,string>("font-emheight.FreesiaUPC", "0.834046019140705"));
			dictMap.insert(pair<string,string>("font-emheight.Gabriola", "0.543236074270557"));
			dictMap.insert(pair<string,string>("font-emheight.Gautami", "0.575928008998875"));
			//dictMap.insert(pair<string,string>("font-emheight.Gentium\u0020Basic", "0.864135021097046"));
			//dictMap.insert(pair<string,string>("font-emheight.Gentium\u0020Book\u0020Basic", "0.864135021097046"));
			dictMap.insert(pair<string,string>("font-emheight.Georgia", "0.880103137086377"));
			dictMap.insert(pair<string,string>("font-emheight.Gisha", "0.853333333333333"));
			dictMap.insert(pair<string,string>("font-emheight.Impact", "0.819855884707766"));
			dictMap.insert(pair<string,string>("font-emheight.IrisUPC", "0.790580968924918"));
			//dictMap.insert(pair<string,string>("font-emheight.Iskoola\u0020Pota", "0.880860215053763"));
			dictMap.insert(pair<string,string>("font-emheight.JasmineUPC", "0.945958429561201"));
			dictMap.insert(pair<string,string>("font-emheight.Kalinga", "0.673684210526316"));
			dictMap.insert(pair<string,string>("font-emheight.Kartika", "0.701129750085587"));
			//dictMap.insert(pair<string,string>("font-emheight.Khmer\u0020UI", "0.883520276100086"));
			dictMap.insert(pair<string,string>("font-emheight.KodchiangUPC", "1.0173869846001"));
			dictMap.insert(pair<string,string>("font-emheight.Kokila", "0.867429055484964"));
			//dictMap.insert(pair<string,string>("font-emheight.Lao\u0020UI", "0.751835535976505"));
			dictMap.insert(pair<string,string>("font-emheight.Latha", "0.728825622775801"));
			dictMap.insert(pair<string,string>("font-emheight.Leelawadee", "0.836259697835851"));
			//dictMap.insert(pair<string,string>("font-emheight.Levenim\u0020MT", "0.757676655567888"));
			//dictMap.insert(pair<string,string>("font-emheight.Liberation\u0020Sans\u0020Narrow", "0.883139284174213"));
			dictMap.insert(pair<string,string>("font-emheight.LilyUPC", "1.04944914168588"));
			//dictMap.insert(pair<string,string>("font-emheight.Lingoes\u0020Unicode", "0.746355685131195"));
			//dictMap.insert(pair<string,string>("font-emheight.Linux\u0020Biolinum\u0020G", "0.877087794432548"));
			//dictMap.insert(pair<string,string>("font-emheight.Linux\u0020Libertine\u0020G", "0.877087794432548"));
			//dictMap.insert(pair<string,string>("font-emheight.Lucida\u0020Sans\u0020Unicode", "0.650778519224658"));
			//dictMap.insert(pair<string,string>("font-emheight.Malgun\u0020Gothic", "0.751835535976505"));
			dictMap.insert(pair<string,string>("font-emheight.Mangal", "0.595348837209302"));
			/*			dictMap.insert(pair<string,string>("font-emheight.Meiryo\u0020UI", "0.787389465590158"));
			dictMap.insert(pair<string,string>("font-emheight.Microsoft\u0020JhengHei", "0.751835535976505"));
			dictMap.insert(pair<string,string>("font-emheight.Microsoft\u0020New\u0020Tai\u0020Lue", "0.764464352370287"));
			dictMap.insert(pair<string,string>("font-emheight.Microsoft\u0020PhagsPa", "0.781679389312977"));
			dictMap.insert(pair<string,string>("font-emheight.Microsoft\u0020Sans\u0020Serif", "0.883520276100086"));
			dictMap.insert(pair<string,string>("font-emheight.Microsoft\u0020Tai\u0020Le", "0.786482334869432"));
			dictMap.insert(pair<string,string>("font-emheight.Microsoft\u0020YaHei", "0.757676655567888"));
			dictMap.insert(pair<string,string>("font-emheight.Microsoft\u0020Yi\u0020Baiti", "0.999024390243902"));
			dictMap.insert(pair<string,string>("font-emheight.Miriam\u0020Fixed", "1.01285855588526"));*/
			dictMap.insert(pair<string,string>("font-emheight.Miriam", "0.99514091350826"));
			//dictMap.insert(pair<string,string>("font-emheight.Mongolian\u0020Baiti", "0.940312213039486"));
			dictMap.insert(pair<string,string>("font-emheight.MoolBoran", "0.745540589734256"));
			//dictMap.insert(pair<string,string>("font-emheight.MV\u0020Boli", "0.620606060606061"));
			dictMap.insert(pair<string,string>("font-emheight.Narkisim", "1.0123578843302"));
			dictMap.insert(pair<string,string>("font-emheight.Nyala", "0.957009345794393"));
			/*		dictMap.insert(pair<string,string>("font-emheight.Palatino\u0020Linotype", "0.741223307998552"));
			dictMap.insert(pair<string,string>("font-emheight.Plantagenet\u0020Cherokee", "0.787995382839554"));*/
			dictMap.insert(pair<string,string>("font-emheight.Raavi", "0.602352941176471"));
			dictMap.insert(pair<string,string>("font-emheight.Rod", "1.01941264310602"));
			/*			dictMap.insert(pair<string,string>("font-emheight.Sakkal\u0020Majalla", "0.716083916083916"));
			dictMap.insert(pair<string,string>("font-emheight.Segoe\u0020Print", "0.573830204539087"));
			dictMap.insert(pair<string,string>("font-emheight.Segoe\u0020Script", "0.631319358816276"));
			dictMap.insert(pair<string,string>("font-emheight.Segoe\u0020UI", "0.751835535976505"));
			dictMap.insert(pair<string,string>("font-emheight.Segoe\u0020UI\u0020Symbol", "0.751835535976505"));
			dictMap.insert(pair<string,string>("font-emheight.Shonar\u0020Bangla", "0.772538664654847"));*/
			dictMap.insert(pair<string,string>("font-emheight.Shruti", "0.594830090037758"));
			//dictMap.insert(pair<string,string>("font-emheight.Simplified\u0020Arabic", "0.603240058910162"));
			//dictMap.insert(pair<string,string>("font-emheight.Simplified\u0020Arabic\u0020Fixed", "0.915921288014311"));
			//dictMap.insert(pair<string,string>("font-emheight.Swiss742\u0020SWC", "0.803452334248725"));
			dictMap.insert(pair<string,string>("font-emheight.Sylfaen", "0.759362254356693"));
			dictMap.insert(pair<string,string>("font-emheight.Symbol", "0.816261458748505"));
			dictMap.insert(pair<string,string>("font-emheight.Tahoma", "0.828478964401295"));
			//dictMap.insert(pair<string,string>("font-emheight.Times\u0020New\u0020Roman", "0.90299823633157"));
			//dictMap.insert(pair<string,string>("font-emheight.Traditional\u0020Arabic", "0.66906239790918"));
			//dictMap.insert(pair<string,string>("font-emheight.Trebuchet\u0020MS", "0.861227922624054"));
			dictMap.insert(pair<string,string>("font-emheight.Tunga", "0.602352941176471"));
			dictMap.insert(pair<string,string>("font-emheight.Utsaah", "0.893542757417103"));
			dictMap.insert(pair<string,string>("font-emheight.Vani", "0.593795302986373"));
			dictMap.insert(pair<string,string>("font-emheight.Verdana", "0.822820409803134"));
			dictMap.insert(pair<string,string>("font-emheight.Vijaya", "0.993210475266731"));
			dictMap.insert(pair<string,string>("font-emheight.Vrinda", "0.732737030411449"));
			dictMap.insert(pair<string,string>("font-emheight.Wingdings", "0.901011878574571"));
			dictMap.insert(pair<string,string>("font-emheight.Meiryo", "0.666666666666667"));

			/*			dictMap.insert(pair<string,string>("font-emheight.Academy\u0020Engraved\u0020LET", "0.870748299319728"));
			dictMap.insert(pair<string,string>("font-emheight.Alma\u0020Iso", "0.997384481255449"));
			dictMap.insert(pair<string,string>("font-emheight.Alma\u0020Large", "1.57250859106529"));
			dictMap.insert(pair<string,string>("font-emheight.Alma\u0020Symbol", "0.997384481255449"));*/
			dictMap.insert(pair<string,string>("font-emheight.AVGmdBU", "1.00986193293886"));


		}

}
