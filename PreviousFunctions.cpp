#include "PreviousHeaders.h"

//===============================================================
// toStrings
//===============================================================

string toString(Point2d* p)
{
    return "(" + int2string(p->x) + "," + int2string(p->y) + ")";
}

string toString(FrameData* fd)
{
    if(fd == 0) {return "NULL";}
    return  toString(fd->position) +
            " f:" + int2string(fd->frameNumber);
}

string toString(PersonData* pd)
{
    string str =    "Frames in video:" +
                    int2string(pd->framesInVideo) +
                    "\nPath: ";
    for(size_t i=0; i<pd->path.size(); i++) {
        str += "[" + toString(pd->path[i]) + "]";
    }
    return str;
}

string toString(VideoData* vd)
{
    string str = "Video Information:\nPixel/meter:" +
                 int2string(vd->pixelsPerMeter) +
                 "\n";
    for(size_t i=0; i<vd->persons.size(); i++) {
        str += "Person" + int2string(i) + ":\n" +
               toString(vd->persons[i]) + "\n";
    }
    return str;
}





//=========================================================
// "Construtores"
//=========================================================

PersonData* string2PersonData(string str)
{
    istringstream istr(str); //Abre uma istringstream para percorrer s string str

    int totalFrames;
    istr >> totalFrames; //Pega o número inicial da linha (a quantidade de frames em que a pessoa permanece no vídeo)

    vector<FrameData*> personPath;
    personPath.reserve(totalFrames);
    istr.ignore(1); //Ignora o espaço imediatamente posterior ao número de frames

    int x, y, currentFrame;
    while(!istr.eof()) { //Itera até chegar ao final da string
        istr.ignore(1);         //Ignora o parêntese "("
        istr >> x;              //Guarda o primeiro número
        istr.ignore(1);         //Ignora a vírgula
        istr >> y;              //Guarda o segundo número
        istr.ignore(1);         //Ignora a vírgula
        istr >> currentFrame;   //Guarda o terceiro número
        istr.ignore(1);         //Ignora o parêntese ")"

        Point2d* p = new Point2d;
        p->x = x;  p->y = y;

        FrameData* fd = new FrameData;
        fd->position = p; fd->frameNumber = currentFrame;

        personPath.push_back(fd);
    }
    PersonData* pd = new PersonData;
    pd->framesInVideo = totalFrames;
    pd->path = personPath;
    return pd;
}

PersonData* pdTest(string str)
{
    PersonData* pd = string2PersonData(str);
    return pd;
}


VideoData* file2VideoData(string file)
{
    ifstream videoFile;
    videoFile.open( file.c_str() ); //É necessário passar a string para o formato C para usar o open
    if (!videoFile.is_open()) {
        return 0;
    }
    string str;

    int ppm; //Pixels por metro
    getline(videoFile, str); //Primeira linha do arquivo contém a informação de pixels por metro
    ppm = getPixelData(str);

    vector<PersonData*> vec;
    while(!videoFile.eof()) { //Itera até o fim do arquivo
        getline(videoFile, str); //Cada linha corresponde à informação de uma pessoa
        if (videoFile.eof()){
            break;  //A última linha não possui caracteres. Este teste impede o uso dela.
        }
        vec.push_back( string2PersonData(str) );
    }
    videoFile.close();
//    for(size_t i=0; i<vec.size(); i++) {
//            cout << vec[i]->toString() << endl;
//    }
    VideoData* vd = new VideoData;
    vd->pixelsPerMeter = ppm;
    vd->persons = vec;
    vd->nOfFrames = findNOfFrames(vec);
    return vd;
}

void zeroFill(VideoData* vd)
{
    for(size_t i=0; i<vd->persons.size(); i++) {
        PersonData* tempPerson = vd->persons[i];
        FrameData* tempFrame = tempPerson->path[0];

        int frameNumber = tempFrame->frameNumber; //primeiro frame

        if (frameNumber > 1) {
            vector<FrameData*>::iterator it = tempPerson->path.begin();
            tempPerson->path.insert(it, frameNumber-1, (FrameData*)0);
            //CANCERCANCERCANCER
        }

        tempFrame = tempPerson->path.back();
        frameNumber = tempFrame->frameNumber; //Ultimo frame em que a pessoa aparece
        if(frameNumber < vd->nOfFrames) {
            for(int i=0; i<vd->nOfFrames - frameNumber; i++) {
                tempPerson->path.push_back((FrameData*) 0);
            }
        }
    }
}



int ultimoFrameGrupo(int** matGrupo, int nPessoas, int nFrames)
{
    int ult = 0;

    for(int i=0; i<nFrames; i++) {

        for(int j=0; j<nPessoas; j++) {

            if(matGrupo[j][i] !=0) {
                ult = i;
                break;
            }

        }

    }
    return ult;
}



//REQUER: vd tenha passado antes por zeroFill
void screenBound(VideoData* vd, Point2d* menores, Point2d* maiores)
{
    int menorX = 1000000;
    int menorY = 1000000;

    int maiorX = 0;
    int maiorY = 0;

    for(size_t i = 0; i < vd->persons.size(); i++){
        PersonData* pd = vd->persons[i];
        for(int j = 0; j < vd->nOfFrames; j++){
            if(pd->path[j] != 0) {
                if(pd->path[j]->position->x < menorX) {
                    menorX = pd->path[j]->position->x;
                }
                if(pd->path[j]->position->y < menorY) {
                    menorY = pd->path[j]->position->y;
                }
                if(pd->path[j]->position->x > maiorX) {
                    maiorX = pd->path[j]->position->x;
                }
                if(pd->path[j]->position->y > maiorY) {
                    maiorY = pd->path[j]->position->y;
                }
            }
        }
    }
    menores->x = menorX;
    menores->y = menorY;
    maiores->x = maiorX;
    maiores->y = maiorY;

}




/*
Recebe a primeira linha do arquivo, ou seja,
Uma string com modelo "[n]"
*/
int getPixelData(string str)
{
    istringstream istr(str);
    int n;
    istr.ignore(1); //Ignora o caractere '['
    istr >> n;      //Guarda o número
    cout << "getPixelData " << n << endl;
    return n;
}

//Encontra o número de frames do vídeo
int findNOfFrames(vector<PersonData*> vec)
{
    int n = 0;
    for(size_t i=0; i<vec.size(); i++) {
        PersonData* pd = vec[i];
        if(pd->path.size() > 0) {
            FrameData* fd = pd->path.back();
            int aux = fd->frameNumber;
            if(aux > n) n = aux;
        }
    }
    return n;
}




bool equals(Point2d* p1, Point2d* p2)
{
    return (p1->x == p2->x && p1->y == p2->y);
}

//faz um vetor dados dois pontos p1 e p2 e um ponteiro para um Point2d
//Retorna um vetor de p1 para p2
void makeVetor(Point2d* p1, Point2d* p2, Point2d* res)
{
    res->x = p1->x - p2->x;
    res->y = p1->y - p2->y;
}

float module(float vx, float vy)
{
    return sqrt( pow(vx, 2.0) + pow(vy, 2.0) );
}

float dotProduct(float v1x, float v1y, float v2x, float v2y)
{
    return v1x*v2x + v1y*v2y;
}


void printMatrix(int** mat, int rows, int cols)
{
    for(int i=0; i<rows; i++){
        for (int j = 0; j<cols; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}


string int2string(size_t n)
{
    ostringstream convert;
    convert << n;
    return convert.str();
}

string int2string(int n)
{
    ostringstream convert;
    convert << n;
    return convert.str();
}

string float2String(float f)
{
    ostringstream convert;
    convert << f;
    return convert.str();
}
