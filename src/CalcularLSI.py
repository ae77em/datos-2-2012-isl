#!/usr/bin/env python
# -*- coding: utf-8 -*-
from struct import *
from gensim import logging, models, corpora, matutils 
import sys, numpy

#sys.argv[1] -> contiene el path a la matriz
#sys.argv[2] -> contiene la cantidad de topicos (autovalores a calcular)
#sys.argv[3] -> contiene la cantidad de columnas a levantar por vez
#sys.argv[4] -> contiene el path donde grabar la SVD


try:
	corpus = corpora.MmCorpus(sys.argv[1]) 
	lsi = models.LsiModel(corpus, num_topics=int(sys.argv[2]), chunksize=int(sys.argv[3]))

	try:
		# Calculo y guardo la Matriz V
		V = matutils.corpus2dense(lsi[corpus], len(lsi.projection.s)).T / lsi.projection.s
		# lo imprimo con 4 decimales
		file = open(sys.argv[4]+"_V.bin", "wb")
		file.write(pack('ii', V.shape[0], V.shape[1]))
		file.write(V)
		file.close()
					
	except Exception:
		print "Error al intentar guardar la matriz V."
		raise
		
	try:
		# Calculo y los autovalores
		S =  lsi.projection.s
		# lo imprimo con 4 decimales
		
#		file = open("ArchConfig/S.bin", "wb")
		file = open(sys.argv[4]+"_S.bin", "wb")
		file.write(pack('i', S.shape[0]))
		file.write(S)
		file.close()
			
	except Exception:
		print "Error al intentar guardar la matriz S."
		raise
		
	try:
		# Calculo y los autovalores
		U =  lsi.projection.u
		
		file = open(sys.argv[4]+"_U.bin", "wb")
		file.write(pack('ii', U.shape[0], U.shape[1]))
		file.write(U)
		file.close()
		
	except Exception:
		print "Error al intentar guardar la matriz U."
		raise
			 
except Exception:
	print "Los argumentos son inválidos o insuficientes."
	raise	

 
