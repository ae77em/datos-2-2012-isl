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
		# Calculo y guardo la Matriz Vt
		V = matutils.corpus2dense(lsi[corpus], len(lsi.projection.s)).T / lsi.projection.s
		
		Vt = transpose(V)
		
		file = open(argv[4] + "_Vt.bin", "wb")
		file.write(pack('ii', Vt.shape[0], Vt.shape[1]))
		file.write(Vt)
		file.close()
					
	except Exception:
		print "Error al intentar guardar la matriz V."
		raise

	try:
		# Calculo los autovalores
		Saux =  lsi.projection.s
		# Calculo la inversa de S, y los almaceno
		S = linalg.pinv(diag(Saux))
				
		file = open(argv[4] + "/S.bin", "wb")
		file.write(pack('i', S.shape[0]))
		file.write(S)
		file.close()
			
	except Exception:
		print "Error al intentar guardar la matriz S."
		raise
		
	try:
		# Calculo y los autovalores
		U =  lsi.projection.u
		
		file = open(argv[4] + "/U.bin", "wb")
		file.write(pack('ii', U.shape[0], U.shape[1]))
		file.write(U)
		file.close()
		
	except Exception:
		print "Error al intentar guardar la matriz U."
		raise
	
	 
except Exception:
	print "Los argumentos son inválidos o insuficientes."
	raise	

 

