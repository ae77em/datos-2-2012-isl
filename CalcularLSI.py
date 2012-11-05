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
	logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO) 
	corpus = corpora.MmCorpus(sys.argv[1]) 
	lsi = models.LsiModel(corpus, num_topics=int(sys.argv[2]), chunksize=int(sys.argv[3]))
				
	try:
		# Guardando Matriz V
		log=open('ArchConfig/MatrizV.txt', 'w')
		sys.stdout=log
		# Calculo y guardo la Matriz V
		V = matutils.corpus2dense(lsi[corpus], len(lsi.projection.s)).T / lsi.projection.s
		# lo imprimo con 4 decimales
		print V
		
		
	except Exception:
		print "Error al intentar guardar la matriz V."
		
	try:
		# Guardando Autovalores
		log=open('ArchConfig/Autovalores.txt', 'w')
		sys.stdout=log		
		# Calculo y los autovalores
		S =  lsi.projection.s
		# lo imprimo con 4 decimales
		print S
		
	
	except Exception:
		print "Error al intentar guardar los autovalores"

	try:
		# Guarda Matriz U
		log=open('ArchConfig/MatrizU.txt', 'w')
		sys.stdout=log		
		# Calculo y los autovalores
		S =  lsi.projection.u
		# lo imprimo con 4 decimales
		print S
		
	
	except Exception:
		print "Error al intentar guardar los autovalores"

			 
except Exception:
	print "Los argumentos son inválidos o insuficientes."
		

