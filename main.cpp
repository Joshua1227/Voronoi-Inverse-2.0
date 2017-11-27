#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>
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
VPoint Vertex[8],tempver[10], last[3], last1[3], last2[3], Khatam[8][3];
polar_point finale[8][3];
circle tempc[4];
double w = 100;
int navi=0;

int orientation_y(VPoint p1, VPoint p2)
{

    float val = atan2((p2.y - p1.y),(p2.x - p1.x)) * 180/M_PI;
 
    if ((val > 0 && val < 90)||(val < 0 && val > -90)) return 1;  // colinear
    
    else if((val > 90 && val <= 180) || (val < -90 && val >= -180)) return -1;
    
    else return 0;
}

int orientation_x(VPoint p1, VPoint p2)
{

    float val = atan2((p2.y - p1.y),(p2.x - p1.x)) * 180/M_PI;
 
    if (val > 0 && val <= 180) return 1;  // colinear
    
    else if(val < 0 && val >= -180 ) return -1;
    
    else return 0;
}

float change_domain_180(float a){
	if(a < 180.0)
		return (360.0 + a);
	else 
		return a;
}
float change_domain_90(float a){
	if(a < 90.0)
		return (360.0 + a);
	else 
		return a;
}

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
	int k=0;
	VEdge edges[15],edges1[10][3];
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
	double direction[10][3];	
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
	P.r = 10;
	P.theta = direction[w][0];
	P.angle_correction();
	Q.r = 10;
	Q.theta = direction[w][1];
	Q.angle_correction();
	while(found == false)						// start seach loop
	{
		polar_point P1 = A.MirrorPoint(P);
		polar_point P2 = B.MirrorPoint(P);
		polar_point P12 = C.MirrorPoint(P1);
		VPoint temp,temp1,temp2,temp12;
		temp = P.ConvertToCoordinate();
		temp1 = P1.ConvertToCoordinate();
		temp2 = P2.ConvertToCoordinate();
		temp12 = P12.ConvertToCoordinate();
		//outfile<<"P -> ("<<P.r<<", "<<P.theta<<") P1 -> ("<<P1.r<<", "<<P1.theta<<") P2 -> ("<<P2.r<<", "<<P2.theta<<") P12 -> ("<<P12.r<<", "<<P12.theta<<")"<<std::endl;
		//KEY AREA//
		if (P2.theta != P12.theta)			// if P is not the vertex
		{
			mirror_Q:
			polar_point Q1 = A.MirrorPoint(Q);
			polar_point Q2 = B.MirrorPoint(Q);
			polar_point Q12 = C.MirrorPoint(Q1);
			VPoint temp,temp1,temp2,temp12;
			temp = Q.ConvertToCoordinate();
			temp1 = Q1.ConvertToCoordinate();
			temp2 = Q2.ConvertToCoordinate();
			temp12 = Q12.ConvertToCoordinate();
			//outfile<<"Q -> ("<<Q.r<<", "<<Q.theta<<") Q1 -> ("<<Q1.r<<", "<<Q1.theta<<") Q2 -> ("<<Q2.r<<", "<<Q2.theta<<") Q12 -> ("<<Q12.r<<", "<<Q12.theta<<")"<<std::endl;
			//KEY AREA//
			
			if((Q2.theta - Q12.theta) != 0.0) 		// if Q is not the vertex
			{
				polar_point pq;
				if((P.theta - Q.theta > 180) || (Q.theta - P.theta > 180))
					pq.theta = (P.theta + Q.theta)/2 - 180;
				else
					pq.theta = (P.theta + Q.theta)/2;
				if(pq.theta < 0)
					pq.theta += 360;
				pq.r = P.r;
				polar_point pq1 = A.MirrorPoint(pq);
				polar_point pq2 = B.MirrorPoint(pq);
				polar_point pq12 = C.MirrorPoint(pq1);
				//outfile<<"PQ -> ("<<pq.r<<", "<<pq.theta<<") PQ1 -> ("<<pq1.r<<", "<<pq1.theta<<") PQ2 -> ("<<pq2.r<<", "<<pq2.theta<<") PQ12 -> ("<<pq12.r<<", "<<pq12.theta<<")"<<std::endl;
				
				if((pq2.theta - pq12.theta < 0.01) && (pq2.theta - pq12.theta > -0.01))
				{
					std::cout<<"negligible difference in 2 & 12"<<std::endl;
					finale[w][0] = pq;
					finale[w][1] = pq1;
					finale[w][2] = pq2;
					found = true;
					outfile.close();
					break;
					
				}
				
				if(pq.theta == P.theta || pq.theta == Q.theta){
					std::cout<<"final point reached"<<std::endl<<Vertex[w].x<<" , "<<Vertex[w].y<<std::endl;
					//outfile<<"final point reached"<<std::endl;
					finale[w][0] = P;
					finale[w][1] = P1;
					finale[w][2] = P2;
					outfile.close();
					break;
				}
				
				if(orientation_y(Q2.ConvertToCoordinate(),Q12.ConvertToCoordinate()) != orientation_y(P2.ConvertToCoordinate(),P12.ConvertToCoordinate())){
				if(  orientation_y(pq2.ConvertToCoordinate(),pq12.ConvertToCoordinate()) == orientation_y(P2.ConvertToCoordinate(),P12.ConvertToCoordinate())){
				// this condition is when the sign of the difference between 2 and 12 for pq is the same as P
					//outfile<<"case 1"<<std::endl;
					P.theta = pq.theta;
				}
				else if(orientation_y(pq2.ConvertToCoordinate(),pq12.ConvertToCoordinate()) == orientation_y(Q2.ConvertToCoordinate(),Q12.ConvertToCoordinate())){
				// this condition is when the sign of the difference between 2 and 12 for pq is the same as Q
					//outfile<<"case 2"<<std::endl;
					Q.theta = pq.theta;
				}
				else{
					std::cout<<"somethings wrong"<<std::endl;
					//exit(0);
				}
				}
				else{
				if(  orientation_x(pq2.ConvertToCoordinate(),pq12.ConvertToCoordinate()) == orientation_x(P2.ConvertToCoordinate(),P12.ConvertToCoordinate())){
				// this condition is when the sign of the difference between 2 and 12 for pq is the same as P
					//outfile<<"case 1"<<std::endl;
					P.theta = pq.theta;
				}
				else if(orientation_x(pq2.ConvertToCoordinate(),pq12.ConvertToCoordinate()) == orientation_x(Q2.ConvertToCoordinate(),Q12.ConvertToCoordinate())){
				// this condition is when the sign of the difference between 2 and 12 for pq is the same as Q
					//outfile<<"case 2"<<std::endl;
					Q.theta = pq.theta;
				}
				else{
					std::cout<<"somethings wrong"<<std::endl;
					//exit(0);
				}
				}
				
			}
			else
				{
					found = true;
					finale[w][0] = Q;
					finale[w][1] = Q1;
					finale[w][2] = Q2;
					outfile.close();
				}
		}
		else
			{
				found = true;
				finale[w][0] = P;
				finale[w][1] = P1;
				finale[w][2] = P2;
				outfile.close();
			}
	}
	}
	//Code will be entered here
	std::cout<<navi<<std::endl;
	for(int i=0;i<navi-1;i++){
		for(int j=1;i+j<navi;j++){
			double tempA, tempB, angle;
			for(int o=0;o<3;o++){
	 		if(Vertex[i+j].x == edges2[i][o].start->x){
	 			double tempa[3];
	 			double tempb[3];
	 			//std::cout<<"case I\n";
	 			for(int z=0;z<3;z++){
	 				tempa[z] = finale[i][z].theta;
	 				tempb[z] = finale[i+j][z].theta;
	 			//	std::cout<<"a "<<finale[i][z].theta<<std::endl;
	 			//	std::cout<<"b "<<finale[i+j][z].theta<<std::endl;
	 			}
	 			//std::sort(tempa,tempa + 3*sizeof(tempa[0]));
	 			//std::sort(tempb,tempb + 3*sizeof(tempb[0]));
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
	 				if(x == 2 && tempb[x] < angle){
	 					tempB = tempb[2];
	 					break;
	 				}
	 			}
	 		}
	 		else if((Vertex[i+j].x == edges2[i][o].end->x)){
	 			double tempa[3];
	 			double tempb[3];
	 			//std::cout<<"case II\n";
	 			for(int z=0;z<3;z++){
	 				tempa[z] = finale[i][z].theta;
	 				tempb[z] = finale[i+j][z].theta;
	 				//std::cout<<"a "<<finale[i][z].theta<<std::endl;
	 				//std::cout<<"b "<<finale[i+j][z].theta<<std::endl;
	 				//std::cout<<"ta "<<tempa[z]<<std::endl;
	 				//std::cout<<"tb "<<tempb[z]<<std::endl;
	 			}
	 			//std::sort(tempa,tempa + 3*sizeof(tempa[0]));
	 			//std::sort(tempb,tempb + 3*sizeof(tempa[0]));
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
		 		
		 		float mA,mB,cA,cB;
		 		mA = tan(tempA*(M_PI/180));
		 		mB = tan(tempB*(M_PI/180));
		 		//std::cout<<"temp A is "<<tempA<<"\n";
		 		//std::cout<<"temp B is "<<tempB<<"\n";
		 		cA = Vertex[i].y - mA*Vertex[i].x;
		 		cB = Vertex[i+j].y - mB*Vertex[i+j].x;
		 		float x = (cB-cA)/(mA-mB);
		 		float y = mA*x + cA;
		 		/*std::cout<<"the x is "<<x<<" The y is "<<y<<std::endl;
		 		std::cout<<"equation 1 is :\n";
		 		std::cout<<"y = "<<mA<<" x + "<<cA<<std::endl;
		 		std::cout<<"equation 2 is :\n";
		 		std::cout<<"y = "<<mB<<" x + "<<cB<<std::endl;*/
		 		float r = sqrt(((x-Vertex[i].x)*(x-Vertex[i].x)) + ((y-Vertex[i].y)*(y-Vertex[i].y)));
		 		for(int y=0;y<3;y++){
		 			//std::cout<<"before:"<<finale[i][y].r<<std::endl;
		 			finale[i][y].r = r;
		 			//std::cout<<"after:"<<finale[i][y].r<<std::endl;
		 			//std::cout<<"distance: "<<r<<std::endl;
		 			//std::cout<<r<<"";
		 		}
		 		r = sqrt(((x-Vertex[i+j].x)*(x-Vertex[i+j].x)) + ((y-Vertex[i+j].y)*(y-Vertex[i+j].y)));
		 		for(int y=0;y<3;y++){
		 			//std::cout<<"before:"<<finale[i+j][y].r<<std::endl;
		 			finale[i+j][y].r = r;
		 			//std::cout<<"after:"<<finale[i+j][y].r<<std::endl;
		 			//std::cout<<"distance: "<<r<<std::endl;
		 			//std::cout<<r<<"\n";
		 		}
	 		
	 	}
	}
	
	for(int i=0;i<navi;i++)
	for(int j=0;j<3;j++)
		Khatam[i][j] = finale[i][j].ConvertToCoordinate();
	for(vor::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i)
	std::cout<<"the  vpoints are "<<(*i)->x<<" "<<(*i)->y<<"\n";
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
	for(int j=0; j<navi; j++){	
		glBegin(GL_POINTS);
 		for(int i=0;i<1000;++i)
  		{
  			glVertex3f(-1+2*(Vertex[j].x/w + finale[j][0].r*cos(2*3.14159*i/1000.0)/w), -1+2*(Vertex[j].y/w + finale[j][0].r*sin(2*3.14159*i/1000.0)/w),0);
 		}
 		glEnd();
	}
	glColor3f(1.0, 1.0, 0.0);
	for(int j=0; j<navi; j++){
		for(int i=0; i<3;i++){
			glBegin(GL_QUADS);
			glVertex2f( -1+2*(Vertex[j].x/w + Khatam[j][i].x/w) -0.005,  -1+2*(Vertex[j].y/w + Khatam[j][i].y/w) - 0.005);
			glVertex2f( -1+2*(Vertex[j].x/w + Khatam[j][i].x/w) +0.005,  -1+2*(Vertex[j].y/w + Khatam[j][i].y/w) - 0.005);
			glVertex2f( -1+2*(Vertex[j].x/w + Khatam[j][i].x/w) +0.005,  -1+2*(Vertex[j].y/w + Khatam[j][i].y/w) + 0.005);
			glVertex2f( -1+2*(Vertex[j].x/w + Khatam[j][i].x/w) -0.005,  -1+2*(Vertex[j].y/w + Khatam[j][i].y/w) + 0.005);
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
