#ifndef __PARSER_H_
#define __PARSER_H_

class Parser {
	private:
		Reader* lector;
		Stemmer* stemmer;
		Persister* persistidor;
	public:
		Parser();
		~Parser();
		std::bool parsearArchivo(std::string nombreArchivo);
};

#endif
