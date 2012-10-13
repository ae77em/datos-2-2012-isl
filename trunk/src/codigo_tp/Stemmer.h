#ifndef __STEMMER_H_
#define __STEMMER_H_

class Stemmer {
	public:
		Stemmer();
		~Stemmer();
		
		std::string stemPalabra(std::string palabra);
};

#endif
