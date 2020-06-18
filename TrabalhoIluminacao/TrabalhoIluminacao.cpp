#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <GL/freeglut.h>
#define janela_altura 480
#define janela_largura 640
int on = 1;
double spin = -2.0f;
unsigned char texto[] = "A - Aco, C - Cobre";
float x = 65.0, y = -1.3, z = 0.21;
void reshape(GLsizei largura, GLsizei altura);
void display();
void keyboard(unsigned char key, int a, int b);
void conf_luz(float ambiente[], float diffuse[], float specular[]);
void girar();
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Ligar GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Display com Duplo Buffer
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
	glutInitWindowPosition(50, 50); // Pos. onde surge a janela
	glutCreateWindow("iluminacao"); // Criar Janela
	glutDisplayFunc(display); // imagem
	//glutIdleFunc(girar);
	glutReshapeFunc(reshape); // config telas
	glutKeyboardFunc(keyboard); // funcoes de teclado
	glutMainLoop(); // loop
	return 0;
}
void girar() {
	spin += 0.4;
	if (spin > 360) {
		spin = 0;
	}
	x += 5;
	glutPostRedisplay();
}
void conf_luz(float ambiente[],float diffuse[], float specular[] )
{
	float posicao[] = { 0.0 + sin(x * 2 * 3.14 / 360), 1.0, y, z };
	float lmodel_ambiente[] = { 0.4, 0.4, 0.4, 0.4 };
	float local_view[] = { 0.0 };
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicao);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}



void reshape(GLsizei largura, GLsizei altura){
	if (altura == 0) altura = 1; // previne a divisão por zero
	GLfloat aspecto = (GLfloat)largura / (GLfloat)altura;
	glViewport(0, 0, largura, altura);
	glMatrixMode(GL_PROJECTION); // manipulando matriz de projeção
	glLoadIdentity(); // zerando a matriz
	gluPerspective(45.0f, aspecto, 0.1f, 100.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // configura fundo sem transparencia
	glEnable(GL_DEPTH_TEST); // alunos devem testar
	glShadeModel(GL_SMOOTH); // acabamento com suavização
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // correcao de perspectiva
}
void display()
{
	glPushMatrix();
	glColor3f(1, 0, 0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, texto);

	glPopMatrix();

	float padrao[] = { 0.0, 0.0, 0.0, 1.0 };
	float mat_ambientee[] = { 0.03,0.03,0.03,1 };
	float mat_diffuse[] = { 0.2,0.2,0.2,0.2};
	float mat_specular[] = { 0.8,0.8,0.8,1.0 };
	float alto_brilho[] = { 128.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // executa a limpeza
	glMatrixMode(GL_MODELVIEW); // operando com a camera de modelos
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -20.0f); // posiciona a piramide
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientee);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, alto_brilho);
	glMaterialfv(GL_FRONT, GL_EMISSION, padrao);

	girar();
	glRotated(spin, 1, 1, 0);
	glutSolidCube(4);
	glutSwapBuffers(); // trocar a matriz da tela por esta aqui.
	glPopMatrix();
}
void keyboard(unsigned char key, int a, int b)
{
	printf("x= %f y= %f z=%f \t", x, y, z);
	//cobre
	float cambiente[] = { 0.5, 0.5, 0.5, 011 };
	float cdiffuse[] = { 0.85, 0.45, 0.25, 0.3 };
	float cspecular[] = { 0.85, 0.45, 0.25, 1 };
	//aço
	float aambiente[] = { 0.5, 0.5, 0.5, 0.1 };
	float adiffuse[] = { 0.2, 0.2, 0.2, 0.2 };
	float aspecular[] = { 1.0, 1.0, 1.0, 1.0 };
	switch (key)
	{
	case 'c':
	{
		conf_luz(cambiente,cdiffuse,cspecular);
		glutPostRedisplay();
	} break;
	case 'a':
	{
		conf_luz(aambiente, adiffuse, aspecular);
		glutPostRedisplay();
	} break;
	case 'o':
	{
		if (on)
		{
			glDisable(GL_LIGHT0);
			on = 0;
		}
		else
		{
			glEnable(GL_LIGHT0);
			on = 1;
		}
		glutPostRedisplay();
	} break;
	case 'x':
	{
		if (x >100) {
			x = 0;
		}
		x += 5;
		conf_luz(cambiente, cdiffuse, cspecular);
			glutPostRedisplay();
	} break;
	case 'z':
	{
		z += 0.01;
		conf_luz(cambiente, cdiffuse, cspecular);
		glutPostRedisplay();
	} break;
	case 'y':
	{
		y += 0.1;
		conf_luz(cambiente, cdiffuse, cspecular);
		glutPostRedisplay();
	} break;
	case 'u':
	{
		y -= 0.1;
		conf_luz(cambiente, cdiffuse, cspecular);
		glutPostRedisplay();
	} break;
	case 's':
	{
		z -= 0.01;
		conf_luz(cambiente, cdiffuse, cspecular);
		glutPostRedisplay();
	} break;
	}
}