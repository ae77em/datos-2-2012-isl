#!/usr/bin/env python
# -*- coding: utf-8 -*-
from gensim import logging, models, corpora 
import sys

#sys.argv[1] -> contiene un string con todos los parametros
lista=argv[1].split(' ')


try:
	logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO) 
	corpus = corpora.MmCorpus(lista[1]) 
	lsi = models.LsiModel(corpus, num_topics=int(lista[2]), chunksize=int(lista[3])) 
except Exception:
	print "Los argumentos son inválidos o insuficientes."
