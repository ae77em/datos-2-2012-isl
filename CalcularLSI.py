#!/usr/bin/env python
# -*- coding: utf-8 -*-
from gensim import logging, models, corpora 
import sys

#sys.argv[1] -> contiene un string con todos los parametros
#sys.argv[2] -> contiene la cantidad de topicos (autovalores a calcular)
#sys.argv[3] -> contiene la cantidad de columnas a levantar por vez

try:
	logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO) 
	corpus = corpora.MmCorpus(sys.argv[1]) 
	lsi = models.LsiModel(corpus, num_topics=int(sys.argv[2]), chunksize=int(sys.argv[3])) 
except Exception:
	print "Los argumentos son inválidos o insuficientes."
