template<class T>
MyMatrix<T>::MyMatrix(const MyMatrix &other){
	if (other.isRagged()){
        tam=NULL;
        matriz=NULL;
        rows = other.rows;
        size = other.size;
        start = new int [rows+1];
        for(int i=0;i<=rows;i++){start[i] = other.start[i];}
        ragged= new T[size];
        for(int i=0;i<size;i++){ragged[i] = other.ragged[i];}
    }
    else{
        start=NULL;
        ragged=NULL;
        rows = other.rows;
	    size = other.size;
	    tam = new int [rows];
        matriz=new T*[rows];
	    for(int i=0;i<rows;i++){
            tam[i]=other.tam[i];
            matriz[i]=new T [tam[i]];
            for (int j = 0; j < tam[i]; j++){
                matriz[i][j]=other.matriz[i][j];
            }
        }
    }
}