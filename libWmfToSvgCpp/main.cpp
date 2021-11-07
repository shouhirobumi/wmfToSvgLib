#include "API_WmfToSvg.h"
#include <fstream>
#include "WmfParser.h"
#include "SvgGdi.h"
#include "IGdi.h"

using namespace WMFConverter;

int inputWmfFile(const char* input, void* output)
{
	string inputFile(input);

	bool compatible = false;
	bool replaceSymbolFont = false;
	
	try
	{
		ifstream input;
		input.open(inputFile, ifstream::in);

		WMFConverter::Wmf::WmfParser *parser = new WMFConverter::Wmf::WmfParser();
		WMFConverter::SvgGdi *gdi = new WMFConverter::SvgGdi(compatible);
		gdi->SetReplaceSymbolFont(replaceSymbolFont);

		parser->Parse(&input, (WMFConverter::IGdi*)gdi, inputFile);


		FILE *fp = (FILE*)output;
		try
		{
			
			gdi->Write(fp);
		}
		catch (exception ee)
		{
			printf("main error line 41: %s \r\n", ee.what());
			return -1;
		}
	}
	catch (exception ee)
	{
		printf("main error line 47: %s \r\n", ee.what());
		return -2;
	}
	return 0;
}
