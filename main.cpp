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
VPoint Vertex[2000000],tempver[2000000], Khatam[2000000][3];
polar_point finale[2000000][3];
double w = 1000;
unsigned long int navi=0;
VEdge edges[6000000],edges1[2000000][3];
VPoint temp[2000000];
int Ptemp[2000000];
VEdge edges2[2000000][3];
double direction[2000000][3];



//int num_of_vpoints ;
int main (int argc, char **argv) 
{
	int num_of_vpoints;
	std::ofstream outfile;
	outfile.open("time_taken(1).csv",std::ios::out | std::ios::app);
	//outfile<<"Number_of_VPoints , Number_of_intersections , Initial_Time , Algorithm_Time , Total_Time\n";
	std::cin>>num_of_vpoints;
	std::cout<<"num_of_vpoints = "<<num_of_vpoints<<"\n";
	clock_t t1, t2, t3;
	using namespace vor;
	VPoint origin(0.0,0.0);
	v = new Voronoi();
	ver = new Vertices();
	//dir = new Vertices();

	srand ( time(NULL) );
	// Set max value of i for number of voronoi points
	for(int i=0; i<=num_of_vpoints; i++) 
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
	t1 = clock();
	int k=0;
	//VEdge edges[6000000],edges1[200][3];
	std::cout<<"edges begin \n";
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i,k++)
	{
		tempver[navi].x = (*i)->start->x;
		tempver[navi].y = (*i)->start->y;
		//std::cout<<"start: ( "<<(*i)->start->x<<" , "<<(*i)->start->y<<" )"<<std::endl;
		navi++;
		tempver[navi].x = (*i)->end->x;
		tempver[navi].y = (*i)->end->y;
		//std::cout<<"end: ( "<<(*i)->end->x<<" , "<<(*i)->end->y<<" )"<<std::endl;
		navi++;
		edges[k] = **i;
	}
	std::cout<<"edges end \n";
	//VPoint temp[200];
	//int Ptemp[200];
	std::cout<<"initializing temp values\n";
	for(int i=0;i<2000000;i++)
		Ptemp[i]=0;
	std::cout<<"done\n";
	int z=0;
	std::cout<<"Ptemp begin\n";
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
	std::cout<<"Ptemp ends\n";
	//VEdge edges2[200][3];
	//double direction[200][3];
	std::cout<<"Final edges, direction begins\n";	
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
			
			if(direction[j][0] < 0.0)
				direction[j][0] += 360.0;
			if(direction[j][1] < 0.0)
				direction[j][1] += 360.0;
			if(direction[j][2] < 0.0)
				direction[j][2] += 360.0;
			/*	
			std::cout<<"Vertex: ( "<<Vertex[j].x<<" , "<<Vertex[j].y<<" ) "<<Ptemp[i]<<std::endl;
			std::cout<<"start0: ( "<<edges2[j][0].start->x<<" , "<<edges2[j][0].start->y<<" ) slope is "<<direction[j][0]<<std::endl;
			std::cout<<"end0: ( "<<edges2[j][0].end->x<<" , "<<edges2[j][0].end->y<<" )"<<std::endl;
			std::cout<<"start1: ( "<<edges2[j][1].start->x<<" , "<<edges2[j][1].start->y<<" ) slope is "<<direction[j][1]<<std::endl;
			std::cout<<"end1: ( "<<edges2[j][1].end->x<<" , "<<edges2[j][1].end->y<<" )"<<std::endl;
			std::cout<<"start2: ( "<<edges2[j][2].start->x<<" , "<<edges2[j][2].start->y<<" ) slope is "<<direction[j][2]<<std::endl;
			std::cout<<"end2: ( "<<edges2[j][2].end->x<<" , "<<edges2[j][2].end->y<<" )"<<std::endl;
			*/
			navi = j;
			j++;
		}
	}
	std::cout<<"ends\n";
	navi+=1;
	t2 = clock();
	std::cout<<"3 point starts\n";
	for(int w=0;w<navi;w++){
	//get slopes  for the lines
	line A(origin, direction[w][0]);					// define the lines
	line B(origin, direction[w][1]);
	line C(origin, direction[w][2]);
	double alpha, beta, gamma;
	double sorted[3] = {direction[w][0], direction[w][1], direction[w][2]};
	if (sorted[0] > sorted[1])
    		std::swap(sorted[0], sorted[1]);
	if (sorted[0] > sorted[2])
    		std::swap(sorted[0], sorted[2]);
	if (sorted[1] > sorted[2])
    		std::swap(sorted[1], sorted[2]);
	//ALPHA
	alpha = 180 - (sorted[2] - sorted[1]);
	//cout<<alpha<<"\n";
	
	//GAMMA
	gamma = 180 - (sorted[1] - sorted[0]);
	//cout<<gamma<<"\n";
	
	polar_point l,l1,l2;
	l.r=10;
	l1.r=10; 
	l2.r=10;
	l.theta = sorted[0] - alpha;
	if(l.theta < 0)
		l.theta += 360;
	l1.theta = sorted[0] + alpha;
	if(l1.theta > 360)
		l1.theta -= 360;
	l2.theta = sorted[2] - gamma;
	if(l2.theta < 0)
		l2.theta += 360;
	
	finale[w][0] = l;
	finale[w][1] = l1;
	finale[w][2] = l2;
	
	}
	std::cout<<"ends\n";
	std::cout<<"4 point starts\n";
	std::cout<<navi<<std::endl;
	
	bool find[200000];
	//Initializing bool values
	for(int i=0;i<navi;i++)
		find[i]=false;
	//running code
	for(int i=0;i<navi;i++){
		if(find[i] == true)
			continue;
		bool found = false;
		for(int j=0;j<navi;j++){
			if (j==i) continue;
			double tempA, tempB, angle;
			for(int o=0;o<3;o++){
	 		if(Vertex[j].x == edges2[i][o].start->x){
	 			found = true;
	 			//std::cout<<"the i is "<<Vertex[i].x<<" "<<Vertex[i].y<<"\n";
	 			//std::cout<<"the j is "<<Vertex[j].x<<" "<<Vertex[j].y<<"\n";
	 			double tempa[3];
	 			double tempb[3];
	 			//std::cout<<"case I\n";
	 			for(int z=0;z<3;z++){
	 				tempa[z] = finale[i][z].theta;
	 				tempb[z] = finale[j][z].theta;
	 				//std::cout<<"a "<<finale[i][z].theta<<std::endl;
	 				//std::cout<<"b "<<finale[j][z].theta<<std::endl;
	 			}
	 			// Sorting tempa
	 			for(int k=0;k<3;k++){
	 				double tempo;
	 				if(tempa[0] > tempa[1]){
	 					tempo = tempa[1];
	 					tempa[1] = tempa[0];
	 					tempa[0] = tempo;
	 				}
	 				if(tempa[0] > tempa[2]){
	 					tempo = tempa[2];
	 					tempa[2] = tempa[0];
	 					tempa[0] = tempo;
	 				}
	 				if(tempa[1] > tempa[2]){
	 					tempo = tempa[2];
	 					tempa[2] = tempa[1];
	 					tempa[1] = tempo;
	 				}
	 			}
	 			//sorting tempb
	 			for(int k=0;k<3;k++){
	 				double tempo;
	 				if(tempb[0] > tempb[1]){
	 					tempo = tempb[1];
	 					tempb[1] = tempb[0];
	 					tempb[0] = tempo;
	 				}
	 				if(tempb[0] > tempb[2]){
	 					tempo = tempb[2];
	 					tempb[2] = tempb[0];
	 					tempb[0] = tempo;
	 				}
	 				if(tempb[1] > tempb[2]){
	 					tempo = tempb[2];
	 					tempb[2] = tempb[1];
	 					tempb[1] = tempo;
	 				}
	 			}
	 			//std::cout<<"tempa are: "<<tempa[0]<<"  "<<tempa[1]<<"  "<<tempa[2]<<std::endl;
	 			//std::cout<<"tempb are: "<<tempb[0]<<"  "<<tempb[1]<<"  "<<tempb[2]<<std::endl;
	 			angle = atan2((edges2[i][o].start->y - edges2[i][o].end->y),(edges2[i][o].start->x - edges2[i][o].end->x))*(180/M_PI);
	 			//std::cout<<"angle is "<<angle<<"\n";
	 			if(angle < 0) angle += 360;
	 			for(int w=0;w<3;w++){
	 				if(tempa[w] > angle){
	 					tempA = tempa[w];
	 					break;
	 				}
	 				if(w == 2 && tempa[w] < angle){
	 					tempA = tempa[0];
	 					break;
	 				}
	 			}
	 			float angle1 = angle;
	 			if(angle > 180) angle1 -= 180;
	 			else angle1 += 180;
	 			for(int x=0;x<3;x++){
	 				if(tempb[x] > angle1){
	 					if(x == 0){
	 						tempB = tempb[2];
	 						break;
	 					}
	 					else{
	 						tempB = tempb[x-1];
	 						break;
	 					}
	 				}
	 				if(x == 2 && tempb[x] < angle1){
	 					tempB = tempb[2];
	 					break;
	 				}
	 			}
	 		}
	 		else if((Vertex[j].x == edges2[i][o].end->x)){
	 			found = true;
	 			//std::cout<<"the i is "<<Vertex[i].x<<" "<<Vertex[i].y<<"\n";
	 			//std::cout<<"the j is "<<Vertex[j].x<<" "<<Vertex[j].y<<"\n";
	 			double tempa[3];
	 			double tempb[3];
	 			//std::cout<<"case II\n";
	 			for(int z=0;z<3;z++){
	 				tempa[z] = finale[i][z].theta;
	 				tempb[z] = finale[j][z].theta;
	 				//std::cout<<"a "<<finale[i][z].theta<<std::endl;
	 				//std::cout<<"b "<<finale[j][z].theta<<std::endl;
	 				//std::cout<<"ta "<<tempa[z]<<std::endl;
	 				//std::cout<<"tb "<<tempb[z]<<std::endl;
	 			}
	 			// Sorting tempa
	 			for(int k=0;k<3;k++){
	 				double tempo;
	 				if(tempa[0] > tempa[1]){
	 					tempo = tempa[1];
	 					tempa[1] = tempa[0];
	 					tempa[0] = tempo;
	 				}
	 				if(tempa[0] > tempa[2]){
	 					tempo = tempa[2];
	 					tempa[2] = tempa[0];
	 					tempa[0] = tempo;
	 				}
	 				if(tempa[1] > tempa[2]){
	 					tempo = tempa[2];
	 					tempa[2] = tempa[1];
	 					tempa[1] = tempo;
	 				}
	 			}
	 			//sorting tempb
	 			for(int k=0;k<3;k++){
	 				double tempo;
	 				if(tempb[0] > tempb[1]){
	 					tempo = tempb[1];
	 					tempb[1] = tempb[0];
	 					tempb[0] = tempo;
	 				}
	 				if(tempb[0] > tempb[2]){
	 					tempo = tempb[2];
	 					tempb[2] = tempb[0];
	 					tempb[0] = tempo;
	 				}
	 				if(tempb[1] > tempb[2]){
	 					tempo = tempb[2];
	 					tempb[2] = tempb[1];
	 					tempb[1] = tempo;
	 				}
	 			}
	 			//std::cout<<"tempa are: "<<tempa[0]<<"  "<<tempa[1]<<"  "<<tempa[2]<<std::endl;
	 			//std::cout<<"tempb are: "<<tempb[0]<<"  "<<tempb[1]<<"  "<<tempb[2]<<std::endl;
	 			angle = atan2((edges2[i][o].end->y - edges2[i][o].start->y),(edges2[i][o].end->x - edges2[i][o].start->x))*(180/M_PI);
	 			//std::cout<<"angle is "<<angle<<"\n";
	 			if(angle < 0) angle += 360;
	 			for(int w=0;w<3;w++){
	 				if(tempa[w] > angle){
	 					tempA = tempa[w];
	 					break;
	 				}
	 				if(w == 2 && tempa[w] < angle){
	 					tempA = tempa[0];
	 					break;
	 				}
	 			}
	 			float angle1 = angle;
	 			if(angle > 180) angle1 -= 180;
	 			else angle1 += 180;
	 			for(int x=0;x<3;x++){
	 				if(tempb[x] > angle1){
	 					if(x == 0){
	 						tempB = tempb[2];
	 						break;
	 					}
	 					else{
	 						tempB = tempb[x-1];
	 						break;
	 					}
	 				}
	 				if(x == 2 && tempb[x] < angle1){
	 					tempB = tempb[2];
	 					break;
	 				}
	 			}
	 		}
	 		else continue;
	 		}
	 		if(found == true){
	 			// This code uses y=mx+c to find the intersections
		 		
		 		float mA,mB,cA,cB;
		 		mA = tan(tempA*(M_PI/180));
		 		mB = tan(tempB*(M_PI/180));
		 		//std::cout<<"temp A is "<<tempA<<"\n";
		 		//std::cout<<"temp B is "<<tempB<<"\n";
		 		cA = Vertex[i].y - mA*Vertex[i].x;
		 		cB = Vertex[j].y - mB*Vertex[j].x;
		 		float x = (cB-cA)/(mA-mB);
		 		float y = mA*x + cA;
		 		//std::cout<<"the x is "<<x<<" The y is "<<y<<std::endl;
		 		//std::cout<<"equation 1 is :\n";
		 		//std::cout<<"y = "<<mA<<" x + "<<cA<<std::endl;
		 		//std::cout<<"equation 2 is :\n";
		 		//std::cout<<"y = "<<mB<<" x + "<<cB<<std::endl;
		 		float r = sqrt(((x-Vertex[i].x)*(x-Vertex[i].x)) + ((y-Vertex[i].y)*(y-Vertex[i].y)));
		 		for(int y=0;y<3;y++){
		 			//std::cout<<"before:"<<finale[i][y].r<<std::endl;
		 			finale[i][y].r = r;
		 			find[i] = true;
		 			//std::cout<<"after:"<<finale[i][y].r<<std::endl;
		 			//std::cout<<"distance: "<<r<<std::endl;
		 			//std::cout<<r<<"";
		 		}
		 		r = sqrt(((x-Vertex[j].x)*(x-Vertex[j].x)) + ((y-Vertex[j].y)*(y-Vertex[j].y)));
		 		for(int y=0;y<3;y++){
		 			//std::cout<<"before:"<<finale[i+j][y].r<<std::endl;
		 			finale[j][y].r = r;
		 			find[j] = true;
		 			//std::cout<<"after:"<<finale[i+j][y].r<<std::endl;
		 			//std::cout<<"distance: "<<r<<std::endl;
		 			//std::cout<<r<<"\n";
		 		}
		 		
	 			break;
	 			
	 		}
	 	}
	}
	std::cout<<"ends\n";
	for(int i=0;i<navi;i++)
	for(int j=0;j<3;j++)
		Khatam[i][j] = finale[i][j].ConvertToCoordinate();
	std::cout<<"Done!!!\n";
	//for(vor::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i)
	//std::cout<<"the  vpoints are "<<(*i)->x<<" "<<(*i)->y<<"\n";
	/*for(int j=0;j<navi;j++)
	for(vor::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i)
	{
		std::cout<<"x is "<<(*i)->x<<" y is "<<(*i)->y<<std::endl;
		for(int k=0;k<navi;k++){
		double m = atan2((Vertex[k].y - (*i)->y),(Vertex[k].x - (*i)->x))*(180/M_PI);
		if(m<0) m+=360;
		std::cout<<"for  the vertex: "<<Vertex[k].x<<" "<<Vertex[k].y<<" and the  vpoint "<<(*i)->x<<" "<<(*i)->y<<" the angle is "<<m<<" the slope is "<<tan(m)<<"\n";
		}
		//std::cout<<"distance is: "<<sqrt(((Vertex[j].x-(*i)->x)*(Vertex[j].x-(*i)->x))+((Vertex[j].y-(*i)->y)*(Vertex[j].y-(*i)->y)))<<std::endl;
	}*/
	t3 = clock();
	float time1 = ((float)t2-(float)t1);
	float time2 = ((float)t3-(float)t2);
	float time3 = ((float)t3-(float)t1);
	time1 = time1 / CLOCKS_PER_SEC;
	time2 = time2 / CLOCKS_PER_SEC;
	time3 = time3 / CLOCKS_PER_SEC;
	//outfile<<num_of_vpoints<<" , "<<navi<<" , "<<time1<<" , "<<time2<<" , "<<time3<<"\n";
	std::cout<<"time for intializeng the graph information is: "<<time1<<"\n";
	std::cout<<"time for performing the algorithm is: "<<time2<<"\n";
	std::cout<<"Overall time taken is: "<<time3<<"\n";
	
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (700, 700); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("You're first OpenGL Window"); // Set the title for the window
	
	//glutTimerFunc(100, onEF, 0);
	onEF(5);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering

	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping

	//glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	//glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events

	glutMainLoop(); // Enter GLUT's main loop
	
	outfile.close();
	return 0;
}

void drawVoronoi()
{
	
	for(vor::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i)
	{
		glBegin(GL_QUADS);
		glVertex2f( -1+2*(*i)->x/w -0.01,  -1+2*(*i)->y/w - 0.01);
		glVertex2f( -1+2*(*i)->x/w +0.01,  -1+2*(*i)->y/w - 0.01);
		glVertex2f( -1+2*(*i)->x/w +0.01,  -1+2*(*i)->y/w + 0.01);
		glVertex2f( -1+2*(*i)->x/w -0.01,  -1+2*(*i)->y/w + 0.01);
		glEnd();
	}

	
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i)
	{
		glBegin(GL_LINES);
		glVertex2f( -1+2*(*i)->start->x/w,  -1+2*(*i)->start->y/w);
		glVertex2f( -1+2*(*i)->end->x/w, -1+2*(*i)->end->y/w);
		glEnd();
		
	}
	//To draw a circle 
	/*
	for(int j=0; j<navi; j++){	
		glColor3f(1.0, 0.5, 0.0);
		glBegin(GL_POINTS);
 		for(int i=0;i<1000;++i)
  		{
  			glVertex3f(-1+2*(Vertex[j].x/w + finale[j][0].r*cos(2*3.14159*i/1000.0)/w), -1+2*(Vertex[j].y/w + finale[j][0].r*sin(2*3.14159*i/1000.0)/w),0);
 		}
 		glEnd();
	}*/
	
	glColor3f(0.0, 1.0, 0.3);
	for(int j=0; j<navi; j++){
		for(int i=0; i<3;i++){
			glBegin(GL_QUADS);
			glVertex2f( -1+2*(Vertex[j].x/w + Khatam[j][i].x/w) -0.008,  -1+2*(Vertex[j].y/w + Khatam[j][i].y/w) - 0.008);
			glVertex2f( -1+2*(Vertex[j].x/w + Khatam[j][i].x/w) +0.008,  -1+2*(Vertex[j].y/w + Khatam[j][i].y/w) - 0.008);
			glVertex2f( -1+2*(Vertex[j].x/w + Khatam[j][i].x/w) +0.008,  -1+2*(Vertex[j].y/w + Khatam[j][i].y/w) + 0.008);
			glVertex2f( -1+2*(Vertex[j].x/w + Khatam[j][i].x/w) -0.008,  -1+2*(Vertex[j].y/w + Khatam[j][i].y/w) + 0.008);
			glEnd();
		}
	}
	// The  following segment is to see whether the directions found intersect
	glColor3f(1.0, 0.0, 0.0);
	for(int j=0; j<navi; j++){
		for(int i=0; i<3; i++){
			polar_point temp = finale[j][i];
			temp.r += 30;
			VPoint tEmp = temp.ConvertToCoordinate();
			glBegin(GL_LINES);
			glVertex2f( -1+2*(Vertex[j].x)/w, -1+2*(Vertex[j].y)/w);
			glVertex2f( -1+2*(Vertex[j].x + tEmp.x)/w, -1+2*(Vertex[j].y + tEmp.y)/w);
			glEnd();
		}
	}
	
	glColor3f(0, 0, 0);
	
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
