#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <fstream>
#include "Voronoi.h"
#include "VPoint.h"
#include "Circle.h"
#include "lines.h"

void display (void);
void onEF (int n);
void reshape (int width, int height);

vor::Voronoi * v;
vor::Vertices * ver; // vrcholy
//vor::Vertices * dir; // smìry, kterými se pohybují
vor::Edges * edg;	 // hrany diagramu
VPoint Vertex[5],tempver[10], last[3], last1[3], last2[3];
double w = 100;

int main (int argc, char **argv) 
{
	using namespace vor;
	VPoint origin(0.0,0.0);
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
	double direction[10][3];	//NOTE: Change the way we get the direction of the line (use start and end point of the line)
	for(int i=0,j=0; i<z; i++)
	{
		if(Ptemp[i]>2)
		{	
			edges2[j][0] = edges1[i][0];
			edges2[j][1] = edges1[i][1];
			edges2[j][2] = edges1[i][2];
			Vertex[j].x = temp[i].x;
			Vertex[j].y = temp[i].y;
			if(int(Vertex[j].x) == int(edges2[j][0].end->x))
				direction[j][0] = atan2((edges2[j][0].start->y - edges2[j][0].end->y),(edges2[j][0].start->x - edges2[j][0].end->x))*(180/M_PI);
			else
				direction[j][0] = atan2((edges2[j][0].end->y - edges2[j][0].start->y),(edges2[j][0].end->x - edges2[j][0].start->x))*(180/M_PI);
				
			if(int(Vertex[j].x) == int(edges2[j][1].end->x))
				direction[j][1] = atan2((edges2[j][1].start->y - edges2[j][1].end->y),(edges2[j][1].start->x - edges2[j][1].end->x))*(180/M_PI);
			else
				direction[j][1] = atan2((edges2[j][1].end->y - edges2[j][1].start->y),(edges2[j][1].end->x - edges2[j][1].start->x))*(180/M_PI);
				
			if(int(Vertex[j].x) == int(edges2[j][2].end->x))
				direction[j][2] = atan2((edges2[j][2].start->y - edges2[j][2].end->y),(edges2[j][2].start->x - edges2[j][2].end->x))*(180/M_PI);
			else
				direction[j][2] = atan2((edges2[j][2].end->y - edges2[j][2].start->y),(edges2[j][2].end->x - edges2[j][2].start->x))*(180/M_PI);
				
			std::cout<<"Vertex: ( "<<Vertex[j].x<<" , "<<Vertex[j].y<<" ) "<<Ptemp[i]<<std::endl;
			std::cout<<"start0: ( "<<edges2[j][0].start->x<<" , "<<edges2[j][0].start->y<<" ) slope is "<<direction[j][0]<<std::endl;
			std::cout<<"end0: ( "<<edges2[j][0].end->x<<" , "<<edges2[j][0].end->y<<" )"<<std::endl;
			std::cout<<"start1: ( "<<edges2[j][1].start->x<<" , "<<edges2[j][1].start->y<<" ) slope is "<<direction[j][1]<<std::endl;
			std::cout<<"end1: ( "<<edges2[j][1].end->x<<" , "<<edges2[j][1].end->y<<" )"<<std::endl;
			std::cout<<"start2: ( "<<edges2[j][2].start->x<<" , "<<edges2[j][2].start->y<<" ) slope is "<<direction[j][2]<<std::endl;
			std::cout<<"end2: ( "<<edges2[j][2].end->x<<" , "<<edges2[j][2].end->y<<" )"<<std::endl;
			navi = j;
			j++;
		}
	}
	navi+=1;
	for(int w=0;w<navi;w++){
	std::ofstream outfile;
	outfile.open("file.txt",std::ios::out | std::ios::trunc);
	bool found = false;
	//get slopes  for the lines
	line A(origin, direction[w][0]);					// define the lines
	line B(origin, direction[w][1]);
	line C(origin, direction[w][2]);
	polar_point P, Q;
	P.r = 20;
	P.theta = direction[w][0];
	Q.r = 20;
	Q.theta = direction[w][1];
	while(found == false)						// start seach loop
	{
		//NOTE (TO DO) :tarnsform the pint to the origin
		//cout<<"mirror P start"<<endl;
		//mirror_P:
		polar_point P1 = A.MirrorPoint(P);
		//P1.angle_correction();
		//bool P1proper;				// make sure P1 is legitimate
		//if(P1.theta < random_angle1)
		//	P1proper = true;
		//else if(P1.theta > (random_angle1 + random_angle2 + random_angle3))
		//	P1proper = true;
		//else
		//	P1proper = false;
		polar_point P2 = B.MirrorPoint(P);
		//P2.angle_correction();
		//bool P2proper;				// make sure P2 is legitimate
		//if(P2.theta > (random_angle1 + random_angle2) && P2.theta < (random_angle1 + random_angle2 + random_angle3))
		//	P2proper = true;
		//else
		//	P2proper = false;
		polar_point P12 = C.MirrorPoint(P1);
		//P12.angle_correction();
		//bool P12proper;				// make sure P12 is legitimate
		//if(P12.theta >  (random_angle1 + random_angle2) && P2.theta < (random_angle1 + random_angle2 + random_angle3))
		//	P12proper = true;
		//else
		//	P12proper = false;
		//if (P12proper == false || P2proper == false)
		//{
		//	P.theta += random_angle2/100;
			//cout<<random_angle1 + random_angle2<<endl;
			//cout<<random_angle1 + random_angle2 + random_angle3<<endl;
			//cout<<"goto p1 "<<P12.theta<<" "<<P2.theta<<endl;
		//	goto mirror_P;
		//}
		/*else if (P1proper == false)
		{
			cout<<random_angle1<<endl;
			cout<<random_angle1 + random_angle2 + random_angle3<<endl;
			P.theta -= random_angle2/100;
			cout<<"goto p2 "<<P1.theta<<" "<<endl;
			goto mirror_P;
		}*/
		//P.angle_correction();
		//P1.angle_correction();
		//P2.angle_correction();
		//P12.angle_correction();
		VPoint temp,temp1,temp2,temp12;
		temp = P.ConvertToCoordinate();
		temp1 = P1.ConvertToCoordinate();
		temp2 = P2.ConvertToCoordinate();
		temp12 = P12.ConvertToCoordinate();
		//outfile<<setprecision(20)<<"P -> ("<<temp.x<<", "<<temp.y<<") P1 -> ("<<temp1.x<<", "<<temp1.y<<") P2 -> ("<<temp2.x<<", "<<temp2.y<<") P12 -> ("<<temp12.x<<", "<<temp12.y<<")"<<endl;
		outfile<<"P -> ("<<P.r<<", "<<P.theta<<") P1 -> ("<<P1.r<<", "<<P1.theta<<") P2 -> ("<<P2.r<<", "<<P2.theta<<") P12 -> ("<<P12.r<<", "<<P12.theta<<")"<<std::endl;
		//cout<<"P finish"<<endl;
		//KEY AREA//
		if (P2.theta != P12.theta)			// if P is not the vertex
		{
			//cout<<"Q start"<<endl;
			mirror_Q:
			polar_point Q1 = A.MirrorPoint(Q);
			//Q1.angle_correction();
			//bool Q1proper;				// make sure Q1 is legitimate
			//if(Q1.theta < random_angle1)
			//	Q1proper = true;
			//else if(P1.theta > (random_angle1 + random_angle2 + random_angle3))
			//	Q1proper = true;
			//else
			//	Q1proper = false;
			polar_point Q2 = B.MirrorPoint(Q);
			//Q2.angle_correction();
			//bool Q2proper;				// make sure Q2 is legitimate
			//if(Q2.theta > (random_angle1 + random_angle2) && Q2.theta < (random_angle1 + random_angle2 + random_angle3))
			//	Q2proper = true;
			//else
			//	Q2proper = false;
			polar_point Q12 = C.MirrorPoint(Q1);
			//Q12.angle_correction();
			//bool Q12proper;				// make sure Q12 is legitimate
			//if(Q12.theta >  (random_angle1 + random_angle2) && Q2.theta < (random_angle1 + random_angle2 + random_angle3))
			//	Q12proper = true;
			//else
			//	Q12proper = false;
			//if (Q2proper == false)
			//{
				//cout<<random_angle1 + random_angle2<<endl;
				//cout<<random_angle1 + random_angle2 + random_angle3<<endl;
			//	Q.theta -= random_angle2/10000;
				//cout<<"goto q1 "<<Q2.theta<<" "<<endl;
			//	goto mirror_Q;
			//}
			/*else if (Q12proper == false || Q1proper == false)
			{
				cout<<random_angle1 + random_angle2<<endl;
				cout<<random_angle1 + random_angle2 + random_angle3<<endl;
				cout<<random_angle1<<endl;
				Q.theta += random_angle2/10000;
				cout<<"goto q2 "<<Q12.theta<<" "<<Q1.theta<<endl;
				goto mirror_Q;
			}*/
			//Q.angle_correction();
			//Q1.angle_correction();
			//Q2.angle_correction();
			//Q12.angle_correction();
			VPoint temp,temp1,temp2,temp12;
			temp = Q.ConvertToCoordinate();
			temp1 = Q1.ConvertToCoordinate();
			temp2 = Q2.ConvertToCoordinate();
			temp12 = Q12.ConvertToCoordinate();
			//outfile<<setprecision(20)<<"Q -> ("<<temp.x<<", "<<temp.y<<") Q1 -> ("<<temp1.x<<", "<<temp1.y<<") Q2 -> ("<<temp2.x<<", "<<temp2.y<<") Q12 -> ("<<temp12.x<<", "<<temp12.y<<")"<<endl<<endl;
			outfile<<"Q -> ("<<Q.r<<", "<<Q.theta<<") Q1 -> ("<<Q1.r<<", "<<Q1.theta<<") Q2 -> ("<<Q2.r<<", "<<Q2.theta<<") Q12 -> ("<<Q12.r<<", "<<Q12.theta<<")"<<std::endl;
			//cout<<"Q finish"<<endl;
			//KEY AREA//
			
			if(Q2.theta != Q12.theta) 		// if Q is not the vertex
			{
				polar_point pq;
				pq.theta = (P.theta + Q.theta)/2;
				pq.r = P.r;
				//pq.angle_correction();
				polar_point pq1 = A.MirrorPoint(pq);
				//pq1.angle_correction();
				polar_point pq2 = B.MirrorPoint(pq);
				//pq2.angle_correction();
				polar_point pq12 = C.MirrorPoint(pq1);
				//pq12.angle_correction();
				outfile<<"PQ -> ("<<pq.r<<", "<<pq.theta<<") PQ1 -> ("<<pq1.r<<", "<<pq1.theta<<") PQ2 -> ("<<pq2.r<<", "<<pq2.theta<<") PQ12 -> ("<<pq12.r<<", "<<pq12.theta<<")"<<std::endl;
				if(pq.theta == P.theta || pq.theta == Q.theta){
					std::cout<<"final point reached"<<std::endl;
					outfile<<"final point reached"<<std::endl;
					exit(0);
				}
				if(pq2.theta > pq12.theta){
					outfile<<"case 1"<<std::endl;
					//cout<<"1) "<<P.theta<<endl;
					//cout<<"1.1) "<<pq.theta<<endl;
					P.theta = pq.theta;
					//cout<<"2) "<<P.theta<<endl;
					//P.angle_correction();
				//	cout<<"3) "<<P.theta<<endl;
				}
				else if(pq2.theta < pq12.theta){
					outfile<<"case 2"<<std::endl;
					Q.theta = pq.theta;
					//Q.angle_correction();
				}
				else if(pq2.theta == pq12.theta){
					outfile<<"case 3"<<std::endl;
					P.theta = pq.theta;
					//P.angle_correction();
				}
				else{
					std::cout<<"somethings wrong"<<std::endl;
					exit(0);
				}
			}
			else
				{
					found = true;
					last[w] = Q.ConvertToCoordinate();
					last1[w] = Q1.ConvertToCoordinate();
					last2[w] = Q2.ConvertToCoordinate();
					outfile.close();
				}
		}
		else
			{
				found = true;
				last[w] = P.ConvertToCoordinate();
				last1[w] = P1.ConvertToCoordinate();
				last2[w] = P2.ConvertToCoordinate();
				outfile.close();
			}
	}
	}
	std::cout<<navi<<std::endl;
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
