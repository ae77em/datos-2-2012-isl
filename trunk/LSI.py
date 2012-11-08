#!/usr/bin/env python
# -*- coding: utf-8 -*-
from gensim import logging, models, corpora, matutils 
import sys, numpy

#sys.argv[1] -> contiene el path a la matriz
#sys.argv[2] -> contiene la cantidad de topicos (autovalores a calcular)
#sys.argv[3] -> contiene la cantidad de columnas a levantar por vez

numpy.set_printoptions(precision=4)
numpy.set_printoptions(threshold='nan')

try:
	corpus = corpora.MmCorpus(sys.argv[1]) 
	lsi = models.LsiModel(corpus, num_topics=int(sys.argv[2]), chunksize=int(sys.argv[3]))

	try:
		# Calculo y guardo la Matriz V
		V = matutils.corpus2dense(lsi[corpus], len(lsi.projection.s)).T / lsi.projection.s
		# lo imprimo con 4 decimales
		
		file = open("V.bin","wb")
		file.write(V)
		file.close()
					
	except Exception:
		print "Error al intentar guardar la matriz V."
		
	try:
		# Calculo y los autovalores
		S =  lsi.projection.s
		# lo imprimo con 4 decimales
		
		file = open("S.bin","wb")
		file.write(S)
		file.close()
			
	except Exception:
		print "Error al intentar guardar la matriz S."

	try:
		# Calculo y los autovalores
		U =  lsi.projection.u
		
		file = open("U.bin","wb")
		file.write(U)
		file.close()
		
	except Exception:
		print "Error al intentar guardar la matriz U."
			 
except Exception:
	print "Los argumentos son inválidos o insuficientes."
		

 
