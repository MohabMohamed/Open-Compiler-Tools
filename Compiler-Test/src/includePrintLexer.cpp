#include "includePrintLexer.h"
#include <OCT/Regex/Compiler.h>
#include <OCT/Cartridge.h>
#include <OCT/InputStream.h>
#include <OCT/Utilities.h>
#include <OCT/Lexer/Token.h>
using namespace std;
using namespace OCT;
using namespace OCT::Lexer;
using namespace OCT::Regex;
using namespace includePrint;

void includePrintLexer::init()
{
	OCT::Regex::Compiler compiler;
	registerToken(compiler.compile("(\n)"), OCT::Lexer::make_token());
	registerToken(compiler.compile("(\r)"), OCT::Lexer::make_token());
	registerToken(compiler.compile("( )"), OCT::Lexer::make_token());
	registerToken(compiler.compile("(\t)"), OCT::Lexer::make_token());
	registerToken(compiler.compile("(\v)"), OCT::Lexer::make_token());
	registerToken(compiler.compile("(\f)"), OCT::Lexer::make_token());
	registerToken(compiler.compile("(.)"), OCT::Lexer::make_token("Unidentified"));
}
includePrintLexer::includePrintLexer()
{
	init();
}