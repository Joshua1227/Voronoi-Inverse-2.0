#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>

#include "Voronoi.h"
#include "VPoint.h"
#include "Circle.h"

void display (void);
void onEF (int n);
void reshape (int width, int height);

vor::Voronoi * v;
vor::Vertices * ver; // vrcholy
//vor::Vertices * dir; // smìry, kterými se pohybují
vor::Edges * edg;	 // hrany diagramu
VPoint Vertex[5],tempver[10];
double w = 100;

int main (int argc, char **argv) 
{
	using namespace vor;

	v = new Voronoi();
	ver = new Vertices();
	//dir = new Vertices();

	srand ( time(NULL) );

	for(int i=0; i<4; i++) 
	{

		ver->push_back(new VPoint( w * (double)rand()/(double)RAND_MAX , w * (double)rand()/(double)RAND_MAX )); 
		//dir->push_back(new VPoint( 0.0, 0.0)); 
	}

	edg = v->GetEdges(ver, w, w);
	std::cout << "voronois done!\n";

	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i)
	{
		if( (*i)->start == 0 )
		{
			std::cout << "chybi zacatek hrany!\n";
			continue;
		}
		if( (*i)->end == 0 )
		{
			std::cout << "chybi konec hrany!\n";
			continue;
		}	
	}
	int navi=0,k=0;
	VEdge edges[15],edges1[10][3];
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i,k++)
	{
		tempver[navi].x = (*i)->start->x;
		tempver[navi].y = (*i)->start->y;
		std::cout<<"start: ( "<<(*i)->start->x<<" , "<<(*i)->start->y<<" )"<<std::endl;
		navi++;
		tempver[navi].x = (*i)->end->x;
		tempver[navi].y = (*i)->end->y;
		std::cout<<"end: ( "<<(*i)->end->x<<" , "<<(*i)->end->y<<" )"<<std::endl;
		navi++;
		edges[k] = **i;
	}
	VPoint temp[10];
	int Ptemp[10] = {0,0,0,0,0,0,0,0,0,0};
	int z=0;
	for(int i=0,j; i<navi; ++i)
	{
		bool ispresent = false;
		for(j=0; j<navi; ++j)
		{
			if(temp[j].x == tempver[i].x && temp[j].y == tempver[i].y)
			{
				ispresent = true;
				break;
			}
			else 
				continue;
		}
		if(ispresent == true)
		{
			Ptemp[j]++;
			if(edges1[j][1].f!=0 && edges1[j][1].f!=0)
				edges1[j][2] = edges[i/2];
			else
				edges1[j][1] = edges[i/2];
		}
		else
		{
			temp[z].x = tempver[i].x;
			temp[z].y = tempver[i].y;
			Ptemp[z]++;
			edges1[z][0] = edges[i/2];
			z++;
		}
	}
	VEdge edges2[10][3];
	for(int i=0,j=0; i<z; i++)
	{
		if(Ptemp[i]>2)
		{	
			edges2[j][0] = edges1[i][0];
			edges2[j][1] = edges1[i][1];
			edges2[j][2] = edges1[i][2];
			Vertex[j].x = temp[i].x;
			Vertex[j].y = temp[i].y;
			std::cout<<"Vertex: ( "<<Vertex[j].x<<" , "<<Vertex[j].y<<" ) "<<Ptemp[i]<<std::endl;
			std::cout<<"start0: ( "<<edges2[j][0].start->x<<" , "<<edges2[j][0].start->y<<" )"<<std::endl;
			std::cout<<"end0: ( "<<edges2[j][0].end->x<<" , "<<edges2[j][0].end->y<<" )"<<std::endl;
			std::cout<<"start1: ( "<<edges2[j][1].start->x<<" , "<<edges2[j][1].start->y<<" )"<<std::endl;
			std::cout<<"end1: ( "<<edges2[j][1].end->x<<" , "<<edges2[j][1].end->y<<" )"<<std::endl;
			std::cout<<"start2: ( "<<edges2[j][2].start->x<<" , "<<edges2[j][2].start->y<<" )"<<std::endl;
			std::cout<<"end2: ( "<<edges2[j][2].end->x<<" , "<<edges2[j][2].end->y<<" )"<<std::endl;
			navi = j;
			j++;
		}
	}
	//VEdge Edge_connected_to_vertex[10][3];
	//std::cout<<navi<<std::endl;
	/*for(int i=0,q=0; i<2; i++)
	{
		for(vor::Edges::iterator j = edg->begin(); j!= edg->end(); ++j)
		{
			if((*j)->start->x == Vertex[i].x && (*j)->start->y == Vertex[i].y)
			{
				Edge_connected_to_vertex[q] = **j;
				//std::cout<<"start: ( "<<(*j)->start->x<<" , "<<(*j)->start->y<<" )"<<std::endl;
				//std::cout<<"end: ( "<<(*j)->end->x<<" , "<<(*j)->end->y<<" )"<<std::endl;
				//std::cout<<"q = "<<q<<std::endl;
				//std::cout<<"vertex = "<<"( "<<Vertex[i].x<<" , "<<Vertex[i].y<<" )"<<std::endl;
				q++;
				std::cout<<"start"<<std::endl;
			}
			else if((*j)->end->x == Vertex[i].x && (*j)->start->y == Vertex[i].y)
			{
				std::cout<<"end"<<std::endl;
				Edge_connected_to_vertex[q] = **j;
				q++;
			}	
		}
	}*/
	
	/*for(int i=0; i<3*navi; i++)
	{
		angles[i] = -1/(Edge_connected_to_vertex[i].f);
		//std::cout<<angles[i]<<std::endl;
	}*/
	
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (600, 600); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("You're first OpenGL Window"); // Set the title for the window
	
	//glutTimerFunc(100, onEF, 0);
	onEF(5);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering

	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping

	//glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	//glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events

	glutMainLoop(); // Enter GLUT's main loop
	
	return 0;
}

void drawVoronoi()
{
	
	//vor::Vertices::iterator j = dir->begin();
	/*for(vor::Vertices::iterator i = ver->begin(); i != ver->end(); ++i)
	{
		(*i)->x += (*j)->x * w/50;
		(*i)->y += (*j)->y * w/50;
		if( (*i)->x > w ) (*j)->x *= -1;
		if( (*i)->x < 0 ) (*j)->x *= -1;

		if( (*i)->y > w ) (*j)->y *= -1;
		if( (*i)->y < 0 ) (*j)->y *= -1;
		++j;
	}*/
	
	
	//edg = v->GetEdges(ver, w, w);
	//std::cout << "voronoi done";
	for(vor::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i)
	{
		glBegin(GL_QUADS);
		//std::cout << (*i)->x << "\n";
		glVertex2f( -1+2*(*i)->x/w -0.01,  -1+2*(*i)->y/w - 0.01);
		glVertex2f( -1+2*(*i)->x/w +0.01,  -1+2*(*i)->y/w - 0.01);
		glVertex2f( -1+2*(*i)->x/w +0.01,  -1+2*(*i)->y/w + 0.01);
		glVertex2f( -1+2*(*i)->x/w -0.01,  -1+2*(*i)->y/w + 0.01);
		glEnd();
	}

	
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i)
	{
		/*
		glBegin(GL_LINES);
		glVertex2f( -1+2*(*i)->left->x/w,  -1+2*(*i)->left->y/w);
		glVertex2f( -1+2*(*i)->right->x/w, -1+2*(*i)->right->y/w);
		glEnd();
		*/
		glBegin(GL_LINES);
		glVertex2f( -1+2*(*i)->start->x/w,  -1+2*(*i)->start->y/w);
		glVertex2f( -1+2*(*i)->end->x/w, -1+2*(*i)->end->y/w);
		glEnd();
		
	}
	//vor::Vertices::iterator j = dir->begin();
	//for(vor::Vertices::iterator i = ver->begin(); i != ver->end(); ++i)
	//{
		//std::cout<<"("<<(*i)->x<<" , "<<(*i)->y<<")"<<std::endl;
		//std::cout<<"("<<(*j)->x<<" , "<<(*j)->y<<")"<<std::endl;
		//++j;
	//}
}

void display (void) 
{
	std::cout << "display\n";
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
	glTranslatef(0.0f, 0.0f, -5.0f); 

	glFlush();
}


void onEF(int n)
{
	
	//glutTimerFunc(20, onEF, 0);
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Clear the background of our window to red  
	
	drawVoronoi();
	glutSwapBuffers();
	//Draw everything to the screen
}

void reshape (int width, int height) 
{
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(22.5, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}
