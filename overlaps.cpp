//Nitro C++ proficiency assessment, coded by Martin Gladnishki
#include <algorithm>
#include <list>
#include <iostream>
#include "overlaps.h"
#include "CParserJson.h"

typedef struct 
{
	CParserVarNumber<_CONST_CHAR("x")> x;
	CParserVarNumber<_CONST_CHAR("y")> y;
	CParserVarNumber<_CONST_CHAR("w")> w;
	CParserVarNumber<_CONST_CHAR("h")> h;
} JSON_rect;

typedef struct
{
    CParserVarArrayPropertyGroup<JSON_rect,_CONST_CHAR("rects")> rects;
} JSON_data;

int main( int argc, char* argv[] )
{
	//handle command line
	std::cout << "Nitro C++ proficiency assessment, coded by Martin Gladnishki" << std::endl;
	std::cout << "FastJsonC++ ver. "<< FASTJSON_MAJOR_VERSION << "." << FASTJSON_MINOR_VERSION << "." << FASTJSON_PATCH_VERSION << std::endl << std::endl;
	if( argc < 2 )
	{
		std::cerr << "Usage: overlaps <input>" << std::endl;
		return 0;
	}
	
    //parse input
	qtree t;
    CParserJson<JSON_data> parser;
    if( !parser.parseFile( argv[1] ) )
		return -1;
	if( parser.getData()->size() > 1 )
	{
		std::cout << "Warning: skipped trailing rectangle list(s)!" << std::endl;
		return -1;
	}
	
	//iterate & validate json tree
	std::cout << "Input:" << std::endl;
    CParserVarArrayPropertyGroup<JSON_data>& jsonData = parser.getData()[0];
	for( UINT ei = 0; ei < jsonData.size(); ei++ )
	{
		//get current element
		CParserVarPropertyGroup<JSON_data>* element = jsonData[ei];
		CParserVarArrayPropertyGroup<JSON_rect,_CONST_CHAR("rects")>& jsonRects = element->rects;
		if( !jsonRects.isParsed() )
		{
			std::cout << "Warning: malformed JSON file: missing list of rectangles!" << std::endl;
			return -1;
		}

		//iterate and validate rectangles
		for( UINT ri = 0; ri < jsonRects.size(); ri++ )
		{
			//validate current rectangle
			CParserVarPropertyGroup<JSON_rect>* curr = jsonRects[ri];
			if( !curr->x.isParsed() )
			{
				std::cout << "\tWarning: skipped rectangle " << ri << ": missing/invalid X origin!" << std::endl;
				continue;
			}
			if( !curr->y.isParsed() )
			{
				std::cout << "\tWarning: skipped rectangle " << ri << ": missing/invalid Y origin!" << std::endl;
				continue;
			}
			if( !curr->w.isParsed() )
			{
				std::cout << "\tWarning: skipped rectangle " << ri << ": missing/invalid width!" << std::endl;
				continue;
			}
			if( !curr->h.isParsed() )
			{
				std::cout << "\tWarning: skipped rectangle " << ri << ": missing/invalid height!" << std::endl;
				continue;
			}
			std::cout << "\t" << ri + 1 << ": Rectangle at (" << curr->x << "," << curr->y << "), w=" << curr->w << ", h=" << curr->h << "." << std::endl;
			
			//add to quadtree
			t.add( rect( vec2( curr->x, curr->y ), curr->w, curr->h, ri + 1 ) );
		}
	}

	//output overlaps
	std::cout << std::endl << "Overlaps:" << std::endl;
	rect_list overlaps;
	t.get_overlaps( overlaps );
	for( rect_list::iterator it = overlaps.begin(); it != overlaps.end(); it++ )
	{
		rect& o = *it;
		if( o.size() < 2 )
			continue;
		std::cout << "\tBetween rectangle ";
		for( std::vector<UINT>::iterator itn = o.begin(); itn != o.end(); )
		{
			std::cout << *itn++;
			if( itn == o.end() )
				continue;
			std::cout << ((++itn == o.end()) ? " and " : ", ");
			itn--;
		}
		std::cout << " at (" << o.u.u.i << "," << o.u.v.i << "), w=" << o.width() << ", h=" << o.height() << "." << std::endl;
	}
	
	return 0;
}
