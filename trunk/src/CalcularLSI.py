#!/usr/bin/env python
# -*- coding: utf-8 -*-
from struct import *
from gensim import logging, models, corpora, matutils 
from sys import *
from numpy import *
from math import *

#sys.argv[1] -> contiene el path a la matriz
#sys.argv[2] -> contiene la cantidad de topicos (autovalores a calcular)
#sys.argv[3] -> contiene la cantidad de columnas a levantar por vez
#sys.argv[4] -> contiene el path donde grabar la SVD

try:
	corpus = corpora.MmCorpus(argv[1])
	lsi = models.LsiModel(corpus, num_topics=int(argv[2]), chunksize=int(argv[3]))
		
	try:
		# Calculo y guardo la matriz V
		V = matutils.corpus2dense(lsi[corpus], len(lsi.projection.s)).T / lsi.projection.s
				
		file = open(argv[4] + "/V.bin", "wb")
		file.write(V)
		file.close()
	except Exception:
		print "Error al intentar guardar la matriz V."
		raise

	try:
		# Calculo los autovalores
		Saux =  lsi.projection.s

		# Calculo la inversa de S, y la almaceno
		S = diag(linalg.pinv(diag(Saux)))
				
		file = open(argv[4] + "/S.bin", "wb")
		file.write(pack('i', S.shape[0]))
		file.write(S)
		file.close()
			
	except Exception:
		print "Error al intentar guardar la matriz S."
		raise
		
	try:
		# Calculo y guardo la matriz U
		U =  lsi.projection.u
		
		file = open(argv[4] + "/U.bin", "wb")
		file.write(U)
		file.close()		
	except Exception:
		print "Error al intentar guardar la matriz U."
		raise	
	 
except Exception:
	print "Los argumentos son inválidos o insuficientes."
	raise
