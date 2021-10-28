#include "cg3d.h"
#include "math.h"

// gcc -c cg2d.c
// gcc -c cg3d.c
// gcc rotate_object.c -o rotate_object cg3d.o cg2d.o bibaux.o -lm -lX11
// ./rotate_object

#define PI 3.14

object3d * rotate_object(object3d * poligono, point3d * axis, float angle) {
    matrix3d* rotation_matrix = (matrix3d *) malloc(sizeof(matrix3d));
    object3d* rotated_polygon = CreateObject3D(poligono->numbers_of_faces);

    float u = axis->x, v = axis->y, w = axis->z;
    float axis_product = u*u + v*v + w*w;

    rotation_matrix->a11 = (u*u + (v*v + w*w)*cos(angle)) / axis_product;
    rotation_matrix->a12 = (u*v * (1-cos(angle)) - w * sqrt(axis_product) * sin(angle)) / axis_product;
    rotation_matrix->a13 = (u*w * (1-cos(angle)) - w * sqrt(axis_product) * sin(angle)) / axis_product;

    rotation_matrix->a21 = (u*v * (1-cos(angle)) + w * sqrt(axis_product) * sin(angle)) / axis_product;
    rotation_matrix->a22 = (v*v + (u*u + w*w)*cos(angle)) / axis_product;
    rotation_matrix->a23 = (v*w * (1-cos(angle)) - u * sqrt(axis_product) * sin(angle)) / axis_product;
    
    rotation_matrix->a31 = (u*w * (1-cos(angle)) - v * sqrt(axis_product) * sin(angle)) / axis_product;
    rotation_matrix->a32 = (v*w * (1-cos(angle)) + u * sqrt(axis_product) * sin(angle)) / axis_product;
    rotation_matrix->a33 = (w*w + (u*u + v*v)*cos(angle)) / axis_product;

    for(int i=0; i<poligono->numbers_of_faces; i++) {
        face *f = &poligono->faces[i];

        for(int j=0; j<f->numbers_of_points; j++) {
            point3d *p = &f->points[j];

            f->points[j] = *LinearTransf3d(rotation_matrix, p);
        }

        rotated_polygon->faces[i] = *f;
    }

    return poligono;
}


int main(void) {
 point3d * p;
 face * f1, * f2, * f3, * f4, * f5;
 object3d * ob, * cob;
 point3d * u, * v, * vu, *xu, * w;
 matrix3d * H;
 object * faces;
 
 palette * palheta;
 bufferdevice * dispositivo;
 window * janela;
 viewport * porta;
 
 float zcp, zpp;
 
 palheta = CreatePalette(6);
 SetColor(0,0,0,palheta);
 SetColor(1,1,1,palheta);
 SetColor(1,1,0,palheta);
 SetColor(1,0,0,palheta);
 SetColor(0,1,0,palheta);
 SetColor(0,0,1,palheta);
 
 p = (point3d *) malloc(sizeof(point3d));
 
 f1 = CreateFace(3);
 p->x = 10.0; 
 p->y = 10.0;
 p->z = 0.0;
 p->color = 1;
 SetPointFace(p,f1);
 p->x = 10.0;
 p->y = 0.0;
 p->z = 15.0;
 p->color = 1;
 SetPointFace(p,f1);
 p->x = 10.0;
 p->y = -10.0;
 p->z = 0.0;
 p->color = 1;
 SetPointFace(p,f1);
 
 f2 = CreateFace(3);
 p->x = -10.0;
 p->y = 10.0;
 p->z = 0.0;
 p->color = 2;
 SetPointFace(p,f2);
 p->x = -10.0;
 p->y = 0.0;
 p->z = 15.0;
 p->color = 2;
 SetPointFace(p,f2);
 p->x = -10.0;
 p->y = -10.0;
 p->z = 0.0;
 p->color = 2;
 SetPointFace(p,f2);
 
 f3 = CreateFace(4);
 p->x = 10.0;
 p->y = 10.0;
 p->z = 0.0;
 p->color = 3;
 SetPointFace(p,f3);
 p->x = 10.0;
 p->y = 0.0;
 p->z = 15.0;
 p->color = 3;
 SetPointFace(p,f3);
 p->x = -10.0;
 p->y = 0.0;
 p->z = 15.0;
 p->color = 3;
 SetPointFace(p,f3);
 p->x = -10.0;
 p->y = 10.0;
 p->z = 0.0;
 p->color = 3;
 SetPointFace(p,f3); 

 f4 = CreateFace(4);
 p->x = 10.0;
 p->y = 0.0;
 p->z = 15.0;
 p->color = 4;
 SetPointFace(p,f4);
 p->x = 10.0;
 p->y = -10.0;
 p->z = 0.0;
 p->color = 4;
 SetPointFace(p,f4);
 p->x = -10.0;
 p->y = -10.0;
 p->z = 0.0;
 p->color = 4;
 SetPointFace(p,f4);
 p->x = -10.0;
 p->y = 0.0;
 p->z = 15.0;
 p->color = 4; 
 SetPointFace(p,f4); 

 f5 = CreateFace(4);
 p->x = 10.0;
 p->y = 10.0;
 p->z = 0.0;
 p->color = 5; 
 SetPointFace(p,f5);
 p->x = 10.0;
 p->y = -10.0;
 p->z = 0.0;
 p->color = 5;
 SetPointFace(p,f5);
 p->x = -10.0;
 p->y = -10.0;
 p->z = 0.0;
 p->color = 5;
 SetPointFace(p,f5);
 p->x = -10.0;
 p->y = 10.0;
 p->z = 0.0;
 p->color = 5;
 SetPointFace(p,f5);
 
 ob = CreateObject3D(5);
 SetObject3D(f1,ob);
 SetObject3D(f2,ob);
 SetObject3D(f3,ob);
 SetObject3D(f4,ob);
 SetObject3D(f5,ob);
 
 w = (point3d *) malloc(sizeof(point3d)); // vetor normal ao plano de visualização (vetor dado!)
 w->x = 0;
 w->y = 0;
 w->z = -1;
 
 vu = (point3d *) malloc(sizeof(point3d)); // view-up (vetor dado!)
 vu->x = 0;
 vu->y = 1;
 vu->z = 0;

 xu = (point3d *) malloc(sizeof(point3d)); // view-up (vetor dado!)
 xu->x = 1;
 xu->y = 0;
 xu->z = 0;

 ob = rotate_object(ob, xu, PI/2);

 u = VectorProduct3d(vu,w); 
 v = VectorProduct3d(w,u);
 
 H = (matrix3d *) malloc(sizeof(matrix3d));
 H->a11 = u->x; H->a12 = u->y; H->a13 = u->z;
 H->a21 = v->x; H->a22 = v->y; H->a23 = v->z;
 H->a31 = w->x; H->a32 = w->y; H->a33 = w->z;
 
 cob = ConvertObjectBase(H,ob);
 
 //faces = ParalProjFaces(cob);
 zpp = 40.0;
 zcp = -45.0;
 faces = PerspProjFaces(cob,zpp,zcp);

 janela = CreateWindow(-30,-30,30,30);
 dispositivo = CreateBuffer(640,480);
 porta = CreateViewPort(0, 0, 639, 479);
 
 DrawObject(&faces[0],janela,porta,dispositivo,3);
 DrawObject(&faces[1],janela,porta,dispositivo,3);
 DrawObject(&faces[2],janela,porta,dispositivo,3);
 DrawObject(&faces[3],janela,porta,dispositivo,3);
 DrawObject(&faces[4],janela,porta,dispositivo,3);
 
 Dump2X(dispositivo,palheta);
 
 return 0; 
 }


