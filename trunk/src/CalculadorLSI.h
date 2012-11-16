#ifndef CALCULADORLSI_H_
#define CALCULADORLSI_H_

class CalculadorLSI {
public:
	CalculadorLSI();
	virtual ~CalculadorLSI();

	void calcularLSI(int, std::string path, std::string);
};

#endif
