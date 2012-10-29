from gensim import logging, models, corpora //inicializa las librerias propias de gensim para calcular la SVD
logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO) //es un logueo que info lo que se va calculando
corpus = corpora.MmCorpus("PATH_MATRIZ") //abre el archivo que contiene la matriz MM
lsi = models.LsiModel(corpus, num_topics=300, chunksize=5000) //calcula la SVD


// los parametros que necesitaria el script serian 
PATH_MATRIZ = ruta  de la matriz
num_topics = el nro que trunca que la matriz
chunksize = cantidad columnas que se levantan de la matriz, la libreria va levantando de a pedazos la matriz
