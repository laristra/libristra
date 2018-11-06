#include <iostream>  // std::cout etc.
#include <cmath>

#include "ristra/elements/elements.h"

namespace ristra {
namespace elements{

// Used by Gauss2/3D to set quadrature points
void LineGaussRuleInfo(
   double &x, 
   double &w, 
   int &m, 
   int &p){

   m--;
   // creating matrices for weights and points
   double g2[2],w3[3],g3[3],w4[4],g4[4],g5[5],w5[5], 
          g6[6],w6[6],g7[7],w7[7],g8[8],w8[8];
   
   g2[0] = -1.0/sqrt(3.0);
   g2[1] = -1.0*g2[0]; 
   
   w3[0] = 5.0/9.0;
   w3[1] = 8.0/9.0;
   w3[2] = w3[0]; 
        
   g3[0] = -sqrt(3.0/5.0);
   g3[1] = 0.0;
   g3[2] = -1.0*g3[0]; 
   
   w4[0] = (1./2.)-sqrt(5./6.)/6.;
   w4[1] = (1./2.)+sqrt(5./6.)/6.;
   w4[2] = w4[1]; 
   w4[3] = w4[0]; 
   
   g4[0] = -sqrt((3.+2.*sqrt(6./5.))/7.);
   g4[1] = -sqrt((3.-2.*sqrt(6./5.))/7.);
   g4[2] = -g4[1]; 
   g4[3] = -g4[0]; 
   
   w5[0] = (322.-13.*sqrt(70.))/900.;
   w5[1] = (322.+13.*sqrt(70.))/900.;
   w5[2] =  512./900.;
   w5[3] = w5[1]; 
   w5[4] = w5[0]; 

   g5[0] = -sqrt(5.+2.*sqrt(10./7.))/3.;
   g5[1] = -sqrt(5.-2.*sqrt(10./7.))/3.;
   g5[2] = 0.0;
   g5[3] = -g5[1]; 
   g5[4] = -g5[0]; 
   
   w6[0] = 0.1713244923791704;
   w6[1] = 0.3607615730481386;
   w6[2] = 0.4679139345726910; 
   w6[3] = w6[2];
   w6[4] = w6[1];
   w6[5] = w6[0];

   g6[0] = -0.9324695142031521;
   g6[1] = -0.6612093864662645;
   g6[2] = -0.2386191860831969;
   g6[3] = -g6[2];
   g6[4] = -g6[1];
   g6[5] = -g6[0];

   w7[0] = 0.1294849661688697;
   w7[1] = 0.2797053914892766;
   w7[2] = 0.3818300505051189;
   w7[3] = 0.4179591836734694;
   w7[4] = w7[2];
   w7[5] = w7[1];
   w7[6] = w7[0];

   g7[0] = -0.9491079123427585;
   g7[1] = -0.7415311855993945;
   g7[2] = -0.4058451513773972;
   g7[3] =  0.0;
   g7[4] = -g7[2];
   g7[5] = -g7[1];
   g7[6] = -g7[0];

   w8[0] = 0.1012285362903763;
   w8[1] = 0.2223810344533745;
   w8[2] = 0.3137066458778873;
   w8[3] = 0.3626837833783620;
   w8[4] = w8[3];
   w8[5] = w8[2];
   w8[6] = w8[1];
   w8[7] = w8[0];
   
   g8[0] = -0.9602898564975363;
   g8[1] = -0.7966664774136267;
   g8[2] = -0.5255324099163290;
   g8[3] = -0.1834346424956498;
   g8[4] = -g8[3];
   g8[5] = -g8[2];
   g8[6] = -g8[1];
   g8[7] = -g8[0];

   if (p==1) {x=0.0;w=2.0;}
   if (p==2) {x=g2[m];w=1.0;}
   if (p==3) {x=g3[m];w=w3[m];}
   if (p==4) {x=g4[m];w=w4[m];}
   if (p==5) {x=g5[m];w=w5[m];}  
   if (p==6) {x=g6[m];w=w6[m];} 
   if (p==7) {x=g7[m];w=w7[m];} 
   if (p==8) {x=g8[m];w=w8[m];} 

   } // end of line rule function      

// Used by Lovatto 1D/2D to set Lobatto quadrature points
void LineLobattoRuleInfo(
   double &x, 
   double &w, 
   int &m, 
   int &p){

   m--;
   // creating matrices for weights and points
   double L2[2],w3[3],L3[3],w4[4],L4[4],L5[5],w5[5], 
          L6[6],w6[6],L7[7],w7[7],L8[8],w8[8];
   
   L2[0] = -1.0;
   L2[1] =  1.0;
   
   w3[0] = 1.0/3.0;
   w3[1] = 4.0/3.0;
   w3[2] = w3[0]; 
        
   L3[0] =  1.0;
   L3[1] =  0.0;
   L3[2] = -1.0; 
   
   w4[0] = 0.1666666666666666666667;
   w4[1] = 0.8333333333333333333333;
   w4[2] = w4[1]; 
   w4[3] = w4[0]; 
   
   L4[0] = -1.0;
   L4[1] = -0.447213595499957939282;
   L4[2] = -L4[1]; 
   L4[3] = -L4[0]; 
   
   L5[0] = -1.0;
   L5[1] = -0.6546536707079771437983;
   L5[2] = 0.0;
   L5[3] = -L5[1]; 
   L5[4] = -L5[0]; 
   
   w5[0] = 0.1;
   w5[1] = 0.544444444444444444444;
   w5[2] = 0.7111111111111111111111;
   w5[3] = w5[1]; 
   w5[4] = w5[0]; 

   L6[0] = -1.0;
   L6[1] = -0.765055323929464692851;
   L6[2] = -0.2852315164806450963142;
   L6[3] = -L6[2];
   L6[4] = -L6[1];
   L6[5] = -L6[0];

   
   w6[0] = 0.06666666666666666666667;
   w6[1] = 0.3784749562978469803166;
   w6[2] = 0.5548583770354863530167;
   w6[3] = w6[2];
   w6[4] = w6[1];
   w6[5] = w6[0];

   L7[0] = -1.0;
   L7[1] = -0.830223896278566929872;
   L7[2] = -0.4688487934707142138038;
   L7[3] =  0.0;
   L7[4] = -L7[2];
   L7[5] = -L7[1];
   L7[6] = -L7[0];

   
   w7[0] = 0.04761904761904761904762;
   w7[1] = 0.276826047361565948011;
   w7[2] = 0.4317453812098626234179;
   w7[3] = 0.487619047619047619048;
   w7[4] = w7[2];
   w7[5] = w7[1];
   w7[6] = w7[0];


   L8[0] = -1.0;
   L8[1] = -0.8717401485096066153375;
   L8[2] = -0.5917001814331423021445;
   L8[3] = -0.2092992179024788687687;
   L8[4] = -L8[3];
   L8[5] = -L8[2];
   L8[6] = -L8[1];
   L8[7] = -L8[0];

   
   w8[0] = 0.03571428571428571428571;
   w8[1] = 0.210704227143506039383;
   w8[2] = 0.3411226924835043647642;
   w8[3] = 0.4124587946587038815671;
   w8[4] = w8[3];
   w8[5] = w8[2];
   w8[6] = w8[1];
   w8[7] = w8[0];
   
   if (p==1) {x=0.0;w=2.0;}
   if (p==2) {x=L2[m];w=1.0;}
   if (p==3) {x=L3[m];w=w3[m];}
   if (p==4) {x=L4[m];w=w4[m];}
   if (p==5) {x=L5[m];w=w5[m];}  
   if (p==6) {x=L6[m];w=w6[m];} 
   if (p==7) {x=L7[m];w=w7[m];} 
   if (p==8) {x=L8[m];w=w8[m];} 

   } // end of Lobatto line rule function      

// setting gauss quadrature points for 2D elements
void Gauss2D(
   vector< vector<double> > &these_g_pts,  // gauss points
   vector< vector<double> > &these_weights,// gauss weights
   vector<double> &tot_g_weight,           // 2D product of gauss weights
   int &quad_order){                       // quadrature order (m)

   int tot_pts = (quad_order*quad_order);    // total quad points in 2D

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j;
      double x,w;
 
      // sets up the i, j, indices for the line rule implimentation

      j = floor(m/quad_order)+1; 
      i = (m+1) - quad_order*(j-1);

      these_weights[m]={1.0,1.0};
      
      // xi direction
      LineGaussRuleInfo(x,w,i,quad_order); // setting pts/weights in i direction
      these_g_pts[m][0]=x; 
      these_weights[m][0]*=w;
          
      // eta direction
      LineGaussRuleInfo(x,w,j,quad_order); // setting pts/weights in j direction
      these_g_pts[m][1]=x; 
      these_weights[m][1]*=w;
   }

    for(int this_vert=0; this_vert < tot_pts; this_vert++){
      
      tot_g_weight[this_vert] = these_weights[this_vert][0] 
                              * these_weights[this_vert][1]; 
   } //end for



   } // end function

// setting gauss quadrature points for 3D elements
void Gauss3D(
   vector< vector<double> > &these_g_pts,   // gauss points
   vector< vector<double> > &these_weights, // gauss weights
   vector<double> &tot_g_weight,            // 3D product of gauss weights
   int &quad_order){                        // quadrature order (n)
   
   // total quad points in 3D
   int tot_pts = (quad_order*quad_order*quad_order);  

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j, k, jj, pn;

      double x,w;
 
      // sets up the i, j, k indices for the line rule implimentation
      int p12 = (quad_order * quad_order);

      k=floor(m/p12)+1; 

      jj=(m+1)-p12*(k-1); 
      j=floor((jj-1)/quad_order)+1;

      i=jj-quad_order*(j-1);  
      
      these_weights[m]={1.0,1.0,1.0};
      
      // xi direction
      LineGaussRuleInfo(x,w,i,quad_order); // setting pts/weights in i direction
      these_g_pts[m][0]=x; 
      these_weights[m][0]*=w;
          
      // eta direction
      LineGaussRuleInfo(x,w,j,quad_order); // setting pts/weights in j direction
      these_g_pts[m][1]=x; 
      these_weights[m][1]*=w;
      
      // mu direction
      LineGaussRuleInfo(x,w,k,quad_order); // setting pts/weights in k direction
      these_g_pts[m][2]=x; 
      these_weights[m][2]*=w;
          
   } // end for    


  for(int this_vert=0; this_vert < tot_pts; this_vert++){
      
      tot_g_weight[this_vert] = these_weights[this_vert][0] 
                              * these_weights[this_vert][1]
                              * these_weights[this_vert][2]; 
   } //end for


   } // end function

// setting Gauss-Lobatto quadrature points for 2D elements
void Lobatto2D(
   vector< vector<double> > &these_L_pts, // gauss points
   vector< vector<double> > &these_weights, // gauss weights
   int &quad_order){ // quadrature order (n)

   int tot_pts = (quad_order*quad_order);    // total quad points in 2D

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j;
      double x,w;
 
      // sets up the i, j, indices for the line rule implimentation

      j = floor(m/quad_order)+1; 
      i = (m+1) - quad_order*(j-1);

      these_weights[m]={1.0,1.0};
      
      // xi direction
      LineLobattoRuleInfo(x,w,i,quad_order); // setting pts/weights in i direction
      these_L_pts[m][0]=x; 
      these_weights[m][0]*=w;
          
      // eta direction
      LineLobattoRuleInfo(x,w,j,quad_order); // setting pts/weights in j direction
      these_L_pts[m][1]=x; 
      these_weights[m][1]*=w;
        
   } // end for

   } // end function

// setting Gauss-Lobatto quadrature points for 3D elements
void Lobatto3D(
   vector< vector<double> > &these_L_pts, // gauss points
   vector< vector<double> > &these_weights, // gauss weights
   int &quad_order){  // quadrature order (n)
   
   // total quad points in 3D
   int tot_pts = (quad_order*quad_order*quad_order);  

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j, k, jj, pn;

      double x,w;
 
      // sets up the i, j, k indices for the line rule implimentation
      int p12 = (quad_order * quad_order);

      k=floor(m/p12)+1; 

      jj=(m+1)-p12*(k-1); 
      j=floor((jj-1)/quad_order)+1;

      i=jj-quad_order*(j-1);  
      
      these_weights[m]={1.0,1.0,1.0};
      
      // xi direction
      LineLobattoRuleInfo(x,w,i,quad_order); // setting pts/weights in i direction
      these_L_pts[m][0]=x; 
      these_weights[m][0]*=w;
          
      // eta direction
      LineLobattoRuleInfo(x,w,j,quad_order); // setting pts/weights in j direction
      these_L_pts[m][1]=x; 
      these_weights[m][1]*=w;
      
      // mu direction
      LineLobattoRuleInfo(x,w,k,quad_order); // setting pts/weights in k direction
      these_L_pts[m][2]=x; 
      these_weights[m][2]*=w;
          
   } // end for        
   } // end function

//defining the jacobian for 2D/3D elements
void jacobian(
   vector< vector<double> > &J_matrix, 
   double &det_J,
   const vector< vector<double> > &vertices, 
   const vector< vector<double> > &this_partial,
   const int &num_nodes,
   const int &dim){
   

   // setting jacobian matrix to all zeros
   for(int j = 0; j < dim; j++){  // looping over dimension
      for(int k = 0; k < dim; k++){ //looping over dimension
         J_matrix[j][k] = 0.0;
      }// end for k
   } // end for j
   
   // solving for the jacobian 
   for(int j = 0; j < dim; j++){  // looping over dimension (partial)
      for(int k = 0; k < dim; k++){ //looping over dimension (vertex position)
         //looping over node positions
         for(int this_x_vert = 0; this_x_vert < num_nodes; this_x_vert++){ 
            J_matrix[j][k] += vertices[this_x_vert][k]
                           * this_partial[this_x_vert][j];
         } // end for num_nodes
      } // end for k
   } // end for j
    

   //calcualate the determinant of the jacobian for 2D/3D matrices
   det_J =  J_matrix[0][0] *(J_matrix[1][1] * (J_matrix[2][2] - (J_matrix[2][2] - 1)*abs(dim-3)) 
         - (J_matrix[2][1] * J_matrix[1][2])*abs(dim-2))  //group 1
         -  J_matrix[0][1] *(J_matrix[1][0] * (J_matrix[2][2] - (J_matrix[2][2] - 1)*abs(dim-3)) 
         - (J_matrix[2][0] * J_matrix[1][2])*abs(dim-2))  // group 2
         +  J_matrix[0][2] *(J_matrix[1][0] *  J_matrix[2][1] 
         -  J_matrix[2][0] * J_matrix[1][1])*(abs(dim-2)); // group 3 
   } // end of jacobian function

//defining the inverse jacobian for 2D element    
void jacobian_inverse_2d(
   vector< vector<double> > &J_inverse, 
   const vector< vector<double> > &jacobian){

   double det = jacobian[0][0]*jacobian[1][1] 
                - jacobian[0][1]*jacobian[1][0];

   J_inverse = {
               {jacobian[1][1]/det, -jacobian[0][1]/det},
               {-jacobian[1][0]/det, jacobian[0][0]/det},
               };
   } // end of 2D jacobin inverse

// defining  the inverse of the Jacobian for 3D elements
void jacobian_inverse_3d(
   vector<vector<double> > &J_inverse_matrix,
   const vector<vector<double> > &jacobian){

   double A_11 = jacobian[1][1]*jacobian[2][2] 
                 - jacobian[1][2]*jacobian[2][1];

   double A_22 = jacobian[2][2]*jacobian[0][0] 
                 - jacobian[2][0]*jacobian[0][2];

   double A_33 = jacobian[0][0]*jacobian[1][1] 
                 - jacobian[0][1]*jacobian[1][0];

   double A_12 = jacobian[1][2]*jacobian[2][0] 
                 - jacobian[1][0]*jacobian[2][2];

   double A_23 = jacobian[2][0]*jacobian[0][1] 
                 - jacobian[2][1]*jacobian[0][0];

   double A_31 = jacobian[0][1]*jacobian[1][2] 
                 - jacobian[0][2]*jacobian[1][1];

   double A_21 = jacobian[2][1]*jacobian[0][2] 
                 - jacobian[0][1]*jacobian[2][2];

   double A_32 = jacobian[0][2]*jacobian[1][0] 
                 - jacobian[1][2]*jacobian[0][0];

   double A_13 = jacobian[1][0]*jacobian[1][1] 
                 - jacobian[2][0]*jacobian[1][1];
 
   double  det = jacobian[0][0]*A_11 + jacobian[0][1]*A_21 
                + jacobian[0][2]*A_31;

   J_inverse_matrix = {
                      {A_11/det, A_12/det, A_13/det},
                      {A_21/det, A_22/det, A_23/det},
                      {A_31/det, A_32/det, A_33/det},
                      };

    } // end of inverse jacobian 


/*
 .-------------------------------. 
| .----------------------------. |
| |    _____       ________    | |
| |   / ___ `.    |_   ___ `.  | |
| |  |_/___) |      | |   `. \ | |
| |   .'____.'      | |    | | | |
| |  / /____       _| |___.' / | |
| |  |_______|    |________.'  | |
| |                            | |
| '----------------------------' |
 '-------------------------------' 
*/

/*
===========================
2D Quad 4 Elements
===========================


 The finite element local point numbering for a 4 node Hexahedral is
 as follows

        Eta
         ^
         |
  3------+-----2
  |      |     |
  |      |     |
  |      |     |
  |      ------+------> Xi   
  |            |
  |            |
  0------------1

*/

double Quad_4_2D::ref_vert[4][2] = // listed as {Xi, Eta}
	{
	{-1.0, -1.0},// 0
	{ 1.0, -1.0},// 1
	{ 1.0,  1.0},// 2
	{-1.0,  1.0},// 3
	};

// calculate a physical position in an element for a given xi,eta
void Quad_4_2D::physical_position(
	vector <double> &x_point, 
	const vector <double> &xi_2D_point, 
	const vector< vector<double> > &vertices){

 	double shape_fcn[8];
 	double check_unity;

 	// calculate the shape functions from each vertex for 0 through 4(xi,eta)
 	for( int this_vert = 0; this_vert < 4; this_vert++ ){
  		shape_fcn[this_vert] = 1.0/4.0
  			* (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
  			* (1.0 + xi_2D_point[1]*ref_vert[this_vert][1]);

   }// end for

   // calculate the position in physical space
   for (int dim = 0; dim < 2; dim++)
      x_point[dim] = 0.0;

      check_unity = 0.0;
      for (int this_vert = 0; this_vert < 4; this_vert++ ){
        	for (int dim = 0; dim < 2; dim++){
         	x_point[dim] += vertices[this_vert][dim]*shape_fcn[this_vert];

         }// end for dim
          
         // check partition of unity
         check_unity += shape_fcn[this_vert];

      } // end for this_vert
       
      // unit test
      //std::cout << "partion of unity quad 4 2D: " << check_unity << std::endl;
            
} // end of physical position functionfunction

// calculate the value for the basis at each node for a given xi,eta
void Quad_4_2D::basis(vector <double> &basis,
                      const vector <double> &xi_2D_point,
                      const vector< vector<double> > &vertices){

   // calculate the shape functions from each vertex for 0 through 4(xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      basis[this_vert] = 1.0/4.0
         * (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_2D_point[1]*ref_vert[this_vert][1]);

   }// end for
}// end of quad4 basis functions


// Partial derivative of shape functions with respect to Xi
void  Quad_4_2D::partial_xi_shape_fcn(
	vector<double>  &quad4_partial_xi, 
   const vector <double> &xi_2D_point) {


   for (int this_vert = 0; this_vert < 4; this_vert++){
    	quad4_partial_xi[this_vert] = (1.0/4.0)
    		* (ref_vert[this_vert][0])
    		* (1.0 + xi_2D_point[1]*ref_vert[this_vert][1]);
   }

}// end of partial xi funciton


// Partial derivative of shape functions with respect to Eta
void  Quad_4_2D::partial_eta_shape_fcn(
	vector<double> &quad4_partial_eta, 
  	const vector <double> &xi_2D_point) {

   for (int this_vert = 0; this_vert < 4; this_vert++){
      quad4_partial_eta[this_vert] = (1.0/4.0)
       	* (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
       	* (ref_vert[this_vert][1]);
   }

}// end of partial eta function

/*
===========================
2D Quad 8 Elements
===========================


 The finite element local point numbering for a 8 node Hexahedral is
 as follows

         Eta
          ^
          |
  3-------6------2
  |       |      |
  |       |      |
  |       |      |
  |       |      |
  7       +------5-----> Xi   
  |              |
  |              |
  |              |
  0------4-------1

*/

double Quad_8_2D::ref_vert[8][2] = // listed as {Xi, Eta}
	{
	//corner nodes
	{-1.0, -1.0},// 0
	{ 1.0, -1.0},// 1
	{ 1.0,  1.0},// 2
	{-1.0,  1.0},// 3
	// midline nodes
	{ 0.0, -1.0},// 4
	{ 1.0,  0.0},// 4
	{ 0.0,  1.0},// 6
	{-1.0,  0.0},// 6
	};


// calculate a physical position in an element for a given xi,eta,
void Quad_8_2D::physical_position(
   vector <double> &x_point, 
   const vector <double> &xi_2D_point, 
   const vector< vector<double> > &vertices){
  
	double shape_fcn[8];
	double check_unity;

	// calculate the shape functions for node 0,1,2,3(xi,eta)
	for( int this_vert = 0; this_vert < 4; this_vert++ ){
   	shape_fcn[this_vert] = 1.0/4.0
      	* (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
      	* (1.0 + xi_2D_point[1]*ref_vert[this_vert][1])
      	* (xi_2D_point[0]*ref_vert[this_vert][0] 
      	+  xi_2D_point[1]*ref_vert[this_vert][1] -1);
	} // end for this_vert


   // calculate the shape functions for node 4,6(xi,eta)
   for( int this_vert = 4; this_vert <= 6; this_vert += 2 ){
      shape_fcn[this_vert] = 1.0/2.0
         * (1.0 - xi_2D_point[0]*xi_2D_point[0])
         * (1.0 + xi_2D_point[1]*ref_vert[this_vert][1]);
   } // end for this_vert

   // calculate the shape functions for node 5,7 (xi,eta)
   for( int this_vert = 5; this_vert <= 7; this_vert += 2 ){
      shape_fcn[this_vert] = 1.0/2.0
         * (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
         * (1.0 - xi_2D_point[1]*xi_2D_point[1]);
   } // end for this_vert

   // calculate the position in physical space
   for (int dim = 0; dim < 2; dim++)
      x_point[dim] = 0.0;

      check_unity = 0.0;
      for (int this_vert = 0; this_vert < 8; this_vert++ ){
         for (int dim = 0; dim < 2; dim++){
            x_point[dim] += vertices[this_vert][dim]*shape_fcn[this_vert];
         } // end for dim
              
         // check partition of unity
         check_unity += shape_fcn[this_vert];
      } // end for this_vert
   
      // unit test
      //std::cout << "partion of unity quad 8 2D: " << check_unity << std::endl;
         
} // end of function

// calculate the value for the basis at each node for a given xi,eta
void Quad_8_2D::basis(vector <double> &basis,
                      const vector <double> &xi_2D_point,
                      const vector< vector<double> > &vertices){

   // calculate the shape functions for node 0,1,2,3(xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      basis[this_vert] = 1.0/4.0
         * (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_2D_point[1]*ref_vert[this_vert][1])
         * (xi_2D_point[0]*ref_vert[this_vert][0] 
         +  xi_2D_point[1]*ref_vert[this_vert][1] -1);
   } // end for this_vert


   // calculate the shape functions for node 4,6(xi,eta)
   for( int this_vert = 4; this_vert <= 6; this_vert += 2 ){
      basis[this_vert] = 1.0/2.0
         * (1.0 - xi_2D_point[0]*xi_2D_point[0])
         * (1.0 + xi_2D_point[1]*ref_vert[this_vert][1]);
   } // end for this_vert

   // calculate the shape functions for node 5,7 (xi,eta)
   for( int this_vert = 5; this_vert <= 7; this_vert += 2 ){
      basis[this_vert] = 1.0/2.0
         * (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
         * (1.0 - xi_2D_point[1]*xi_2D_point[1]);
   } // end for this_vert
}// end of quad8 basis functions

// Partial derivative of shape functions with respect to Xi
void Quad_8_2D::partial_xi_shape_fcn(
	vector<double>  &quad8_partial_xi, 
   const vector <double> &xi_2D_point) {

   // calculate the Xi partials for node 0,1,2,3 (xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      quad8_partial_xi[this_vert] = 1.0/4.0
         * (ref_vert[this_vert][0])
         * (1 + ref_vert[this_vert][1]*xi_2D_point[1])
         *((2 * ref_vert[this_vert][0]*xi_2D_point[0]) 
         + (ref_vert[this_vert][1]*xi_2D_point[1]));
   } // end for this_vert


   // calculate the Xi partials for node 4,6 (xi,eta)
   for( int this_vert = 4; this_vert <= 6; this_vert += 2 ){
      quad8_partial_xi[this_vert] = -1
         * (xi_2D_point[0])
         * (1 + ref_vert[this_vert][1]*xi_2D_point[1]);
   } // end for this_vert

   // calculate the Xi partials for node 5,7 (xi,eta)
   for( int this_vert = 5; this_vert <= 7; this_vert += 2 ){
      quad8_partial_xi[this_vert] = 1.0/2.0
         * (ref_vert[this_vert][0])
         * (1 - xi_2D_point[1]*xi_2D_point[1]);
   } // end for this_vert

} // end partial Xi function

// Partial derivative of shape functions with respect to Eta
void Quad_8_2D::partial_eta_shape_fcn(
	vector<double> &quad8_partial_eta, 
   const vector <double> &xi_2D_point) {

   // calculate the Eta partials for node 0,1,2,3 (xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      quad8_partial_eta[this_vert] = 1.0/4.0
         * (1 + ref_vert[this_vert][0]*xi_2D_point[0])
         * (ref_vert[this_vert][1])
         *((ref_vert[this_vert][0]*xi_2D_point[0])
         + (2 * ref_vert[this_vert][1]*xi_2D_point[1])); 
   } // end for this_vert

   // calculate the Eta partials for node 4,6 (xi,eta)
   for( int this_vert = 4; this_vert <= 6; this_vert += 2 ){
      quad8_partial_eta[this_vert] = 1.0/2.0
         * (1 - xi_2D_point[0]*xi_2D_point[0])
         * (ref_vert[this_vert][1]);
   } // end for this_vert

   // calculate the Eta partials for node 5,7 (xi,eta)
   for( int this_vert = 5; this_vert <= 7; this_vert += 2 ){
     quad8_partial_eta[this_vert] = -1
        * (1 + ref_vert[this_vert][0]*xi_2D_point[0])
        * (xi_2D_point[1]);
   } // end for this_vert

} // end partial Eta function

/*
===========================
2D Quad 12 Elements
===========================


 The finite element local point numbering for a 8 node Hexahedral is
 as follows (NEED TO DEFINE)

         Eta
          ^
          |
  3---7------6---2
  |       |      |
  |       |      |
 11       |      10
  |       |      |
  |       +------|-----> Xi   
  |              |
  8              9
  |              |
  0----4-----5---1

*/
      
double Quad_12_2D::ref_vert[12][2] = // listed as {Xi, Eta}
   {
   //corner nodes
   {-1.0, -1.0},// 0
   { 1.0, -1.0},// 1
   { 1.0,  1.0},// 2
   {-1.0,  1.0},// 3
   // Eta +- 1./3.
   {-1./3., -1.0},// 4
   { 1./3., -1.0},// 5
   { 1./3.,  1.0},// 6
   {-1./3.,  1.0},// 7
   // Xi +- 1./3.
   {-1.0, -1./3.},// 8
   { 1.0, -1./3.},// 9
   { 1.0,  1./3.},// 10
   {-1.0,  1./3.},// 11
   };

// calculate a physical position in an element for a given xi,eta,
void Quad_12_2D::physical_position(
   vector <double> &x_point, 
   const vector <double> &xi_point,
   const vector< vector<double> > &vertices){
  
	double shape_fcn[12];
	double check_unity;

   // calculate the shape functions for node 0,1,2,3(xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      shape_fcn[this_vert] = 1.0/32.0
         * (1 + ref_vert[this_vert][0] * xi_point[0])
         * (1 + ref_vert[this_vert][1] * xi_point[1])
         * (9.0 * (xi_point[0] * xi_point[0] + xi_point[1] * xi_point[1])
         - (10.0));

   } // end for this_vert


   // calculate the shape functions for node 4-7(xi,eta)
   for( int this_vert = 4; this_vert <= 7; this_vert++ ){
      shape_fcn[this_vert] = 9.0/32.0
         * (1 - xi_point[0] * xi_point[0])
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         * (1 + 9.0 * xi_point[0] * ref_vert[this_vert][0]);

   } // end for this_vert

   // calculate the shape functions for node 8-11 (xi,eta)
   for( int this_vert = 8; this_vert <= 11; this_vert++ ){
      shape_fcn[this_vert] = 9.0/32.0
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         * (1 - xi_point[1] * xi_point[1])
         * (1 + 9.0 * xi_point[1] * ref_vert[this_vert][1]);

   } // end for this_vert

  	// calculate the position in physical space
  	for (int dim = 0; dim < 2; dim++)
     	x_point[dim] = 0.0;

  		check_unity = 0.0;
     	for (int this_vert = 0; this_vert < 12; this_vert++ ){
        	for (int dim = 0; dim < 2; dim++){
          	x_point[dim] += vertices[this_vert][dim]*shape_fcn[this_vert];
        	} // end for dim
              
        // check partition of unity
        check_unity += shape_fcn[this_vert];
     } // end for this_vert
   
   // unit test
   //std::cout << "partion of unity quad 12 2D: " << check_unity << std::endl;

} // end of function

// calculate the value for the basis at each node for a given xi,eta
void Quad_12_2D::basis(vector <double> &basis,
                       const vector <double> &xi_2D_point,
                       const vector< vector<double> > &vertices){

   // calculate the shape functions for node 0,1,2,3(xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      basis[this_vert] = 1.0/4.0
         * (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_2D_point[1]*ref_vert[this_vert][1])
         * (xi_2D_point[0]*ref_vert[this_vert][0] 
         +  xi_2D_point[1]*ref_vert[this_vert][1] -1);
   } // end for this_vert


   // calculate the shape functions for node 4,6(xi,eta)
   for( int this_vert = 4; this_vert <= 6; this_vert += 2 ){
      basis[this_vert] = 1.0/2.0
         * (1.0 - xi_2D_point[0]*xi_2D_point[0])
         * (1.0 + xi_2D_point[1]*ref_vert[this_vert][1]);
   } // end for this_vert

   // calculate the shape functions for node 5,7 (xi,eta)
   for( int this_vert = 5; this_vert <= 7; this_vert += 2 ){
      basis[this_vert] = 1.0/2.0
         * (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
         * (1.0 - xi_2D_point[1]*xi_2D_point[1]);
   } // end for this_vert

}// end of quad12 basis functions

// Partial derivative of shape functions with respect to Xi
void Quad_12_2D::partial_xi_shape_fcn(
	vector<double>  &quad12_partial_xi, 
   const vector <double> &xi_point) {

   // calculate the Xi partials for node 0,1,2,3 (xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      quad12_partial_xi[this_vert] = 1.0/32.0
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         *((9.0 * ref_vert[this_vert][0] 
         * (xi_point[0] * xi_point[0] + xi_point[1] * xi_point[1]))
         + (18.0 * xi_point[0] * (1 + xi_point[0] * ref_vert[this_vert][0]))
         - (10.0 * ref_vert[this_vert][0]));


   } // end for this_vert

   // calculate the Xi partials for node 4,5,6,7 (xi,eta)
   for( int this_vert = 4; this_vert < 8; this_vert++ ){
      quad12_partial_xi[this_vert] = (9.0/32.0) 
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         *((9.0 * ref_vert[this_vert][0] 
         * (1 - 3 * xi_point[0]*xi_point[0]))
         - (2 * xi_point[0]));

   } // end for this_vert

   // calculate the Xi partials for node 8,9,10,11 (xi,eta)
   for( int this_vert = 8; this_vert <= 11; this_vert++){
      quad12_partial_xi[this_vert] = 9.0/32.0
         * (ref_vert[this_vert][0])
         * (1 - xi_point[1] * xi_point[1])
         * (1 + 9 * xi_point[1] * ref_vert[this_vert][1]);


   } // end for this_vert
} // end partial Xi function

// Partial derivative of shape functions with respect to Eta
void Quad_12_2D::partial_eta_shape_fcn(
	vector<double> &quad12_partial_eta, 
   const vector <double> &xi_point) {

   // calculate the Eta partials for node 0,1,2,3 (xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      quad12_partial_eta[this_vert] = 1.0/32.0
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         *((9.0 * ref_vert[this_vert][1] 
         * (xi_point[0] * xi_point[0] + xi_point[1] * xi_point[1]))
         + (18.0 * xi_point[1] * (1 + xi_point[1] * ref_vert[this_vert][1]))
         - (10.0 * ref_vert[this_vert][1]));

   } // end for this_vert


   // calculate the Eta partials for node 4,5,6,7 (xi,eta)
   for( int this_vert = 4; this_vert <= 7; this_vert++ ){
      quad12_partial_eta[this_vert] = 9.0/32.0
         * (1 - xi_point[0] * xi_point[0])
         * (1 + 9 * xi_point[0] * ref_vert[this_vert][0])
         * (ref_vert[this_vert][1]);

   } // end for this_vert

   // calculate the Eta partials for node 8,9,10,11 (xi,eta)
   for( int this_vert = 8; this_vert <= 11; this_vert++){
     quad12_partial_eta[this_vert] = 9.0/32.0
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         *((9.0 * ref_vert[this_vert][1] * (1 - 3 * xi_point[1]*xi_point[1]))
         - (2 * xi_point[1]));

   } // end for this_vert

} // end partial Eta function

/* 
 .-------------------------------. 
| .----------------------------. |
| |    ______      ________    | |
| |   / ____ `.   |_   ___ `.  | |
| |   `'  __) |     | |   `. \ | |
| |   _  |__ '.     | |    | | | |
| |  | \____) |    _| |___.' / | |
| |   \______.'   |________.'  | |
| |                            | |
| '----------------------------' |
 '------------------------------' 
*/


/*
==========================
  Hex 8
==========================

 The finite element local point numbering for a 8 node Hexahedral is
 based on the Ensight manual and illstrated below

         j
         |     k    
         |    /
         |   /
     7---+----6
    /|   |   /|
   / |   |  / |
  4--------5  |
  |  |    -|--+---> i
  |  |     |  |
  |  3-----|--2
  | /      | /       
  |/       |/
  0--------1
 
 Note: left hand coordinate coordinates
*/

double Hex8::ref_vert[8][3] = // listed as {Xi, Eta, Mu}
   {
   // Bottom Nodes
   {-1.0, -1.0, -1.0},// 0
   {+1.0, -1.0, -1.0},// 1
   {+1.0, -1.0, +1.0},// 2
   {-1.0, -1.0, +1.0},// 3
   // Top Nodes
   {-1.0, +1.0, -1.0},// 4
   {+1.0, +1.0, -1.0},// 5
   {+1.0, +1.0, +1.0},// 6
   {-1.0, +1.0, +1.0},// 7
   };

// get the physical location for a given xi_point
void Hex8::physical_position (
	vector <double> &x_point,
   const vector <double> &xi_point,
   const vector< vector<double> > &vertices){

   double shape_fcn[8];
   double check_unity;

   // calculate the shape functions from each vertex for (xi,eta,mu)
   for (int this_vert = 0; this_vert < 8; this_vert++ ){
      shape_fcn[this_vert] = 1.0/8.0
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

   // calculate the position in physical space
   for (int dim = 0; dim < 3; dim++)
      x_point[dim] = 0.0;

   check_unity = 0.0;
   for (int this_vert = 0; this_vert < 8; this_vert++ ){
      
      for (int dim = 0; dim < 3; dim++){
         x_point[dim] += vertices[this_vert][dim]*shape_fcn[this_vert];
      } // end for dim
   
      // check partition of unity
      check_unity += shape_fcn[this_vert];
   } // end for this_vert
    
} // end of function

// calculate the value for the basis at each node for a given xi,eta, mu
void Hex8::basis(vector <double> &basis,
            const vector <double> &xi_point,
            const vector< vector<double> > &vertices){
// calculate the shape functions from each vertex for (xi,eta,mu)
   for (int this_vert = 0; this_vert < 8; this_vert++ ){
      basis[this_vert] = 1.0/8.0
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

} // end of hex8 basis functions

// calculate the partials of the shape function 
// with respect to Xi
void Hex8::partial_xi_shape_fcn(
	vector<double> &hex8_partial_xi, 
   const vector <double> &xi_point) {


   for (int this_vert = 0; this_vert < 8; this_vert++){

      hex8_partial_xi[this_vert] = (1.0/8.0)
         * (ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   }   // end for this_vert

} // end of partial Xi function

// with respect to Eta
void Hex8::partial_eta_shape_fcn(
	vector<double> &hex8_partial_eta, 
   const vector <double> &xi_point) {

   for (int this_vert = 0; this_vert < 8; this_vert++){
      hex8_partial_eta[this_vert] = (1.0/8.0)
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

} //end of partial eta function 

// with repsect to Mu
void Hex8::partial_mu_shape_fcn(
	vector<double> &hex8_partial_mu, 
   const vector <double> &xi_point) {

   for (int this_vert = 0; this_vert < 8; this_vert++){
      hex8_partial_mu[this_vert] = (1.0/8.0)
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (ref_vert[this_vert][2]);
   } // end for this_vert
} // end of partial Mu function
/*

==========================
  Hex 20
==========================

The finite element local point numbering for a 20 node Hexahedral is 
based on the Ensight manual and illstrated below

           j
           |     k
           |    /
           |   /

      7----14----6
     /|         /|
   15 |       13 |
   / 19       /  18
  4----12----5   |
  |   |      |   |  --> i
  |   |      |   |
  |   3---10-|---2
 16  /      17  /
  | 11       | 9         
  |/         |/
  0-----8----1

 Note: left hand coordinate system
*/

double Hex20::ref_vert[20][3] = // listed as {Xi, Eta, Mu}
   {
   // bottom corners
   {-1.0, -1.0, -1.0},// 0
   {+1.0, -1.0, -1.0},// 1
   {+1.0, -1.0, +1.0},// 2
   {-1.0, -1.0, +1.0},// 3
   // top corners
   {-1.0, +1.0, -1.0},// 4
   {+1.0, +1.0, -1.0},// 5
   {+1.0, +1.0, +1.0},// 6
   {-1.0, +1.0, +1.0},// 7
   // bottom edges
   { 0.0, -1.0, -1.0},// 8
   {+1.0, -1.0,  0.0},// 9
   { 0.0, -1.0, +1.0},// 10
   {-1.0, -1.0,  0.0},// 11
   // top edges
   { 0.0, +1.0, -1.0},// 12
   {+1.0, +1.0,  0.0},// 13
   { 0.0, +1.0, +1.0},// 14
   {-1.0, +1.0,  0.0},// 15
   // middle edges
   {-1.0,  0.0, -1.0},// 16
   {+1.0,  0.0, -1.0},// 17
   {+1.0,  0.0, +1.0},// 18
   {-1.0,  0.0, +1.0},// 19
   };


// get the physical location for a given xi_point
void Hex20::physical_position (
	vector <double> &x_point,
   const vector <double> &xi_point,
   const vector< vector<double> > &vertices){


   double shape_fcn[20];
   double check_unity;


   // calculate the 8 corner shape functions for (xi,eta,mu)
   for (int this_vert=0; this_vert<8; this_vert++){
      shape_fcn[this_vert] = 1.0/8.0
         * (1.0 +  xi_point[0]*ref_vert[this_vert][0])
         * (1.0 +  xi_point[1]*ref_vert[this_vert][1])
         * (1.0 +  xi_point[2]*ref_vert[this_vert][2])
         * (xi_point[0]*ref_vert[this_vert][0]
         +  xi_point[1]*ref_vert[this_vert][1]
         +  xi_point[2]*ref_vert[this_vert][2] - 2.0);
   } // end for this_vert

   // calculate the i=0 edge shape functions pts=[8,10,12,14]
   for (int this_vert=8; this_vert<=14; this_vert+=2){
      shape_fcn[this_vert] = 1.0/4.0
         * (1.0 - xi_point[0]*xi_point[0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

   // calculate the j=0 edge shape functions pts=[16,17,18,19]
   for (int this_vert=16; this_vert<=19; this_vert++){
      shape_fcn[this_vert] = 1.0/4.0
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 - xi_point[1]*xi_point[1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

   // calculate the k=0 edge shape functions pts=[9,11,15,13]
   for (int this_vert=9; this_vert<=15; this_vert+=2){
      shape_fcn[this_vert] = 1.0/4.0
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 - xi_point[2]*xi_point[2]);
   } // end for this_vert


   // calculate the position in physical space
   for (int dim=0; dim<3; dim++)
      x_point[dim] = 0.0;

   check_unity = 0.0;
   for (int dim=0; dim<3; dim++){
      for (int this_vert=0; this_vert<20; this_vert++ ){
         x_point[dim] += vertices[this_vert][dim]*shape_fcn[this_vert];

      }   
   } // end for this_vert

   for (this_vert=0; this_vert<20; this_vert++ ){
      // check partition of unity
      check_unity += shape_fcn[this_vert];
   }

   //std::cout << "partion of unity :" << check_unity << std::endl;
} // end of physical position function

// calculate the value for the basis at each node for a given xi,eta, mu
void Hex20::basis(vector <double> &basis,
            const vector <double> &xi_point,
            const vector< vector<double> > &vertices){

   // calculate the 8 corner shape functions for (xi,eta,mu)
   for (int this_vert=0; this_vert<8; this_vert++){
      basis[this_vert] = 1.0/8.0
         * (1.0 +  xi_point[0]*ref_vert[this_vert][0])
         * (1.0 +  xi_point[1]*ref_vert[this_vert][1])
         * (1.0 +  xi_point[2]*ref_vert[this_vert][2])
         * (xi_point[0]*ref_vert[this_vert][0]
         +  xi_point[1]*ref_vert[this_vert][1]
         +  xi_point[2]*ref_vert[this_vert][2] - 2.0);
   } // end for this_vert

   // calculate the i=0 edge shape functions pts=[8,10,12,14]
   for (int this_vert=8; this_vert<=14; this_vert+=2){
      basis[this_vert] = 1.0/4.0
         * (1.0 - xi_point[0]*xi_point[0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

   // calculate the j=0 edge shape functions pts=[16,17,18,19]
   for (int this_vert=16; this_vert<=19; this_vert++){
      basis[this_vert] = 1.0/4.0
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 - xi_point[1]*xi_point[1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

   // calculate the k=0 edge shape functions pts=[9,11,15,13]
   for (int this_vert=9; this_vert<=15; this_vert+=2){
      basis[this_vert] = 1.0/4.0
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 - xi_point[2]*xi_point[2]);
   } // end for this_vert
} // end of hex20 basis functions

// Calculate the partials of the shape functions
// with respect to Xi
void  Hex20::partial_xi_shape_fcn(
	vector<double> &hex20_partial_xi, 
   const vector <double> &xi_point) {

   // For 8 Corner shape functions pts=[0,1,2,3,4,5,6,7]
   for (int this_vert=0; this_vert<8; this_vert++){
      hex20_partial_xi[this_vert] = (1.0/8.0) 
         * (ref_vert[this_vert][0])
         * (1 + (xi_point[1]*ref_vert[this_vert][1]))
         * (1 + (xi_point[2]*ref_vert[this_vert][2]))
         * (2 * (xi_point[0]*ref_vert[this_vert][0])
         + xi_point[1]*ref_vert[this_vert][1]
         + xi_point[2]*ref_vert[this_vert][2] - 1);  
   } // end for this_vert

   // for the i=0 edge shape functions pts=[8,10,12,14]
   for (int this_vert=8; this_vert<=14; this_vert+=2){
      hex20_partial_xi[this_vert] = (-1.0/2.0)
         * (xi_point[0])
         * (1 + xi_point[1]*ref_vert[this_vert][1])
         * (1 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

   // for the k=0 shape functions pts=[9,11,13,15]
   for (int this_vert = 9; this_vert <= 15; this_vert += 2){
      hex20_partial_xi[this_vert] = (1.0/4.0)
         * (ref_vert[this_vert][0])
         * (1 + xi_point[1]*ref_vert[this_vert][1])
         * (1 - xi_point[2]*xi_point[2]);
   } // end for this_vert


   // for the j=0 edge shape functions pts=[16,17,18,19]
   for (int this_vert=16; this_vert<=19; this_vert++){
      hex20_partial_xi[this_vert] = (1.0/4.0)
         * (ref_vert[this_vert][0])
         * (1 - xi_point[1]*xi_point[1])
         * (1 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert
} // end of partial Xi function

// with respect to Eta
void Hex20::partial_eta_shape_fcn(
	vector<double> &hex20_partial_eta, 
   const vector <double> &xi_point) {

   // For 8 Corner shape functions pts=[0,1,2,3,4,5,6,7]
   for (int this_vert=0; this_vert < 8; this_vert++){
      hex20_partial_eta[this_vert] = (1.0/8.0)
         * (1 + xi_point[0]*ref_vert[this_vert][0])
         * (ref_vert[this_vert][1])
         * (1 + xi_point[2]*ref_vert[this_vert][2])
         * (xi_point[0]*ref_vert[this_vert][0]
         + 2 * xi_point[1]*ref_vert[this_vert][1]
         + xi_point[2]*ref_vert[this_vert][2] - 1);
   } // end for this_vert

   // for the i=0 edge shape functions pts=[8,10,12,14]
   for (int this_vert=8; this_vert<=14; this_vert+=2){
      hex20_partial_eta[this_vert] = (1.0/4.0)
         * (1 - (xi_point[0]*xi_point[0]))
         * (ref_vert[this_vert][1])
         * (1 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert

   // for the k=0 shape functions pts=[9,11,13,15]
   for (int this_vert=9; this_vert<=15; this_vert+=2){
      hex20_partial_eta[this_vert] = (1.0/4.0)
         * (1 + xi_point[0]*ref_vert[this_vert][0])
         * (ref_vert[this_vert][1])
         * (1 - (xi_point[2]*xi_point[2]));
   } // end for this_vert

   // for the j=0 edge shape functions pts=[16,17,18,19]
   for (int this_vert=16; this_vert<=19; this_vert++){
      hex20_partial_eta[this_vert] = (-1.0/2.0)
         * (1 + xi_point[0]*ref_vert[this_vert][0])
         * (xi_point[1])
         * (1 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert
} // end of partial Eta function

// with repsect to mu
void Hex20::partial_mu_shape_fcn(
	vector<double> &hex20_partial_mu, 
   const vector <double> &xi_point) {

   // For 8 Corner shape functions pts=[0,1,2,3,4,5,6,7]
   for (int this_vert=0; this_vert < 8; this_vert++){
      hex20_partial_mu[this_vert] = (1.0/8.0)
         * (1 + xi_point[0]*ref_vert[this_vert][0])
         * (1 + xi_point[1]*ref_vert[this_vert][1])
         * (ref_vert[this_vert][2])
         * ((xi_point[0]*ref_vert[this_vert][0])
         + (xi_point[1]*ref_vert[this_vert][1])
         + (2 * xi_point[2]*ref_vert[this_vert][2]) - 1);
   } // end for this_vert

   // for the i=0 edge shape functions pts=[8,10,12,14]
   for (int this_vert=8; this_vert<=14; this_vert+=2){
      hex20_partial_mu[this_vert] = (1.0/4.0)
         * (1 - (xi_point[0]*xi_point[0])) 
         * (1 + xi_point[1]*ref_vert[this_vert][1])
         * (ref_vert[this_vert][2]);
   }

   // for the k=0 shape functions pts=[9,11,13,15]
   for (int this_vert = 9; this_vert <= 15; this_vert += 2){
      hex20_partial_mu[this_vert] = (-1.0/2.0)
         * (1 + xi_point[0]*ref_vert[this_vert][0])
         * (1 + xi_point[1]*ref_vert[this_vert][1])
         * (xi_point[2]);
   } // end for this_vert

   // for the j=0 edge shape functions pts=[16,17,18,19]
   for (int this_vert = 16; this_vert <= 19; this_vert++){
      hex20_partial_mu[this_vert] = (1.0/4.0)
         * (1 + xi_point[0]*ref_vert[this_vert][0])
         * (1 - xi_point[1]*xi_point[1])
         * (ref_vert[this_vert][2]);
   } // end for this_vert
} // end of partial Mu function




/* 

==========================
  Hex 32
==========================

The finite element local point numbering for a 32 node Hexahedral is 
shown below


               Eta
                ^         Mu
                |        /
                |       /
                       /
        7----23------22----6
       /|                 /|
     15 |               14 |
     /  |               /  |
   12  31             13   30 
   /    |             /    |
  4-----20-----21----5     |
  |     |            |     |   ----> Xi
  |    27            |     26  
  |     |            |     |
 28     |           29     |
  |     3----19------|18---2
  |    /             |    /
  |  11              |   10
 24  /              25  /
  | 8                | 9         
  |/                 |/
  0----16------17----1

 Note: left hand coordinate system
*/


double Hex32::ref_vert[32][3] = // listed as {Xi, Eta, Mu}
   {
   {-1.0, -1.0, -1.0},// 0
   {+1.0, -1.0, -1.0},// 1
   {+1.0, -1.0, +1.0},// 2
   {-1.0, -1.0, +1.0},// 3
   {-1.0, +1.0, -1.0},// 4
   {+1.0, +1.0, -1.0},// 5
   {+1.0, +1.0, +1.0},// 6
   {-1.0, +1.0, +1.0},// 7
   // Xi/Eta = +- 1
   {-1.0, -1.0, -1./3.},// 8
   { 1.0, -1.0, -1./3.},// 9
   { 1.0, -1.0,  1./3.},// 10
   {-1.0, -1.0,  1./3.},// 11
   {-1.0,  1.0, -1./3.},// 12
   { 1.0,  1.0, -1./3.},// 13
   { 1.0,  1.0,  1./3.},// 14
   {-1.0,  1.0,  1./3.},// 15
   // Eta/Mu = +- 1
   {-1./3., -1.0, -1.0},// 16
   { 1./3., -1.0, -1.0},// 17
   { 1./3., -1.0,  1.0},// 18
   {-1./3., -1.0,  1.0},// 19
   {-1./3.,  1.0, -1.0},// 20
   { 1./3.,  1.0, -1.0},// 21
   { 1./3.,  1.0,  1.0},// 22
   {-1./3.,  1.0,  1.0},// 23
   // Xi/Mu = +- 1
   {-1.0, -1./3., -1.0},// 24
   { 1.0, -1./3., -1.0},// 25
   { 1.0, -1./3.,  1.0},// 26
   {-1.0, -1./3.,  1.0},// 27
   {-1.0,  1./3., -1.0},// 28
   { 1.0,  1./3., -1.0},// 29
   { 1.0,  1./3.,  1.0},// 30
   {-1.0,  1./3.,  1.0},// 31
   };


// get the physical location for a given xi_point
void Hex32::physical_position (
	vector <double> &x_point,
   const vector <double> &xi_point,
   const vector< vector<double> > &vertices){

   double shape_fcn[32];
   double check_unity;


   // calculate the 8 corner shape functions for (xi,eta,mu)
   for (int this_vert = 0; this_vert < 8; this_vert++){
      shape_fcn[this_vert] = 1.0/64.0 
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2])
         * (9.0 * xi_point[0]*xi_point[0]
         +  9.0 * xi_point[1]*xi_point[1]
         +  9.0 * xi_point[2]*xi_point[2] - 19.0);  
   } // end for this_vert

   // calculate the edge shape functions for pts=[8-15]
   for (int this_vert = 8; this_vert <= 15; this_vert++){
      shape_fcn[this_vert] = 9.0/64.0 
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + 9 * xi_point[2]*ref_vert[this_vert][2])
         * (1.0 - xi_point[2]*xi_point[2]); 
     
   } // end for this_vert

   // calculate the edge shape functions for pts=[16-23]
   for (int this_vert = 16; this_vert <= 23; this_vert++){
      shape_fcn[this_vert] = 9.0/64.0
         * (1.0 - xi_point[0]*xi_point[0])
         * (1.0 + 9 * xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]); 
     
   } // end for this_vert

   // calculate the edge shape functions for pts=[24-31]
   for (int this_vert = 24; this_vert <= 31; this_vert++){
      shape_fcn[this_vert] = 9.0/64.0
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 - xi_point[1]*xi_point[1])
         * (1.0 + 9 * xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]); 
     
   } // end for this_vert


   // calculate the position in physical space
   for (int dim=0; dim<3; dim++)
      x_point[dim] = 0.0;

   for (int this_vert = 0; this_vert <= 31; this_vert++ ){
      for (int dim = 0; dim < 3; dim++){
         x_point[dim] += vertices[this_vert][dim]*shape_fcn[this_vert];
      }
   }
   
   // check partition of unity
   check_unity = 0.0;
   for (int this_vert = 0; this_vert < 32; this_vert++ ){
      check_unity += shape_fcn[this_vert];

   } // end for this_vert

   // unit test
   //std::cout << "Hex 32 partion of unity:" << check_unity << std::endl;

} // end of physical position function

// calculate the value for the basis at each node for a given xi,eta, mu
void Hex32::basis(vector <double> &basis,
            const vector <double> &xi_point,
            const vector< vector<double> > &vertices){

   // calculate the 8 corner shape functions for (xi,eta,mu)
   for (int this_vert = 0; this_vert < 8; this_vert++){
      basis[this_vert] = 1.0/64.0 
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2])
         * (9.0 * xi_point[0]*xi_point[0]
         +  9.0 * xi_point[1]*xi_point[1]
         +  9.0 * xi_point[2]*xi_point[2] - 19.0);  
   } // end for this_vert

   // calculate the edge shape functions for pts=[8-15]
   for (int this_vert = 8; this_vert <= 15; this_vert++){
      basis[this_vert] = 9.0/64.0 
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + 9 * xi_point[2]*ref_vert[this_vert][2])
         * (1.0 - xi_point[2]*xi_point[2]); 
     
   } // end for this_vert

   // calculate the edge shape functions for pts=[16-23]
   for (int this_vert = 16; this_vert <= 23; this_vert++){
      basis[this_vert] = 9.0/64.0
         * (1.0 - xi_point[0]*xi_point[0])
         * (1.0 + 9 * xi_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]); 
     
   } // end for this_vert

   // calculate the edge shape functions for pts=[24-31]
   for (int this_vert = 24; this_vert <= 31; this_vert++){
      basis[this_vert] = 9.0/64.0
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (1.0 - xi_point[1]*xi_point[1])
         * (1.0 + 9 * xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]); 
     
   } // end for this_vert
} // end of hex20 basis functions

// Calculate the partials of the shape functions
// with respect to Xi
void  Hex32::partial_xi_shape_fcn(
	vector<double> &hex32_partial_xi, 
   const vector <double> &xi_point) {

   // calculate the 8 corner partial wrt Xi 
   for (int this_vert = 0; this_vert < 8; this_vert++){
      hex32_partial_xi[this_vert] = 1.0/64.0 
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         * (1 + xi_point[2] * ref_vert[this_vert][2])
         *((9.0 * (ref_vert[this_vert][0])
         * (xi_point[0]*xi_point[0] +  xi_point[1]*xi_point[1] +  xi_point[2]*xi_point[2]))
         + (18.0 * xi_point[0] * (1 + xi_point[0]*ref_vert[this_vert][0]))
         - (19.0 * ref_vert[this_vert][0]));
   } // end for this_vert

   // calculate the edge partial wrt Xi for pts=[8-15]
   for (int this_vert = 8; this_vert <= 15; this_vert++){
      hex32_partial_xi[this_vert] = 9.0/64.0 
         * (ref_vert[this_vert][0])
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         * (1 + 9.0 * xi_point[2] * ref_vert[this_vert][2])
         * (1 - xi_point[2] * xi_point[2]);
   } // end for this_vert

   // calculate the edge partial wrt Xi for pts=[16-23]
   for (int this_vert = 16; this_vert <= 23; this_vert++){
      hex32_partial_xi[this_vert] = 9.0/64.0 
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         * (1 + xi_point[2] * ref_vert[this_vert][2])
         * (9.0 * ref_vert[this_vert][0] * (1 - 3 * xi_point[0] * xi_point[0])
         - (2 * xi_point[0]));
   } // end for this_vert

   // calculate the edge partial wrt Xi for pts=[24-31]
   for (int this_vert = 24; this_vert <= 31; this_vert++){
      hex32_partial_xi[this_vert] = 9.0/64.0 
         * (ref_vert[this_vert][0])
         * (1 - xi_point[1] * xi_point[1])
         * (1 + 9.0 * xi_point[1] * ref_vert[this_vert][1])
         * (1 + xi_point[2] * ref_vert[this_vert][2]);
   } // end for this_vert

} // end of partial Xi function

// with respect to Eta
void Hex32::partial_eta_shape_fcn(
	vector<double> &hex32_partial_eta, 
   const vector <double> &xi_point) {

   // calculate the 8 corner partial wrt Eta 
   for (int this_vert = 0; this_vert < 8; this_vert++){
      hex32_partial_eta[this_vert] = 1.0/64.0 
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         * (1 + xi_point[2] * ref_vert[this_vert][2])
         *((9.0 * ref_vert[this_vert][1]
         * (xi_point[0]*xi_point[0] 
         +  xi_point[1]*xi_point[1]
         +  xi_point[2]*xi_point[2]))
         + (18.0 * xi_point[1] * (1 + xi_point[1]*ref_vert[this_vert][1]))
         - (19.0 * ref_vert[this_vert][1]));
   } // end for this_vert

   // calculate the edge partial wrt Eta for pts=[8-15]
   for (int this_vert = 8; this_vert <= 15; this_vert++){
      hex32_partial_eta[this_vert] = 9.0/64.0 
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         * (ref_vert[this_vert][1])
         * (1 + 9.0 * xi_point[2] * ref_vert[this_vert][2])
         * (1 - xi_point[2] * xi_point[2]);
   } // end for this_vert

   // calculate the edge partial wrt Eta for pts=[16-23]
   for (int this_vert = 16; this_vert <= 23; this_vert++){
      hex32_partial_eta[this_vert] = 9.0/64.0 
         * (1 - xi_point[0] * xi_point[0])
         * (1 + 9.0 * xi_point[0] * ref_vert[this_vert][0])
         * (ref_vert[this_vert][1])
         * (1 + xi_point[2] * ref_vert[this_vert][2]);
   } // end for this_vert

   // calculate the edge partial wrt Eta for pts=[24-31]
   for (int this_vert = 24; this_vert <= 31; this_vert++){
      hex32_partial_eta[this_vert] = 9.0/64.0 
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         * (1 + xi_point[2] * ref_vert[this_vert][2])
         *((9.0 * ref_vert[this_vert][1] * (1 - 3 * xi_point[1] * xi_point[1]))
         - (2 * xi_point[1]));
   } // end for this_vert

} // end of partial Eta function

// with repsect to mu
void Hex32::partial_mu_shape_fcn(
	vector<double> &hex32_partial_mu, 
   const vector <double> &xi_point) {

   // calculate the 8 corner partial wrt Mu 
   for (int this_vert = 0; this_vert < 8; this_vert++){
      hex32_partial_mu[this_vert] = 1.0/64.0 
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         *((9.0 * (ref_vert[this_vert][2])
         * (xi_point[0]*xi_point[0] 
         +  xi_point[1]*xi_point[1]
         +  xi_point[2]*xi_point[2])) 
         + (18.0 * xi_point[2] * (1 + xi_point[2]*ref_vert[this_vert][2]))
         - (19.0 * ref_vert[this_vert][2]));
   } // end for this_vert

   // calculate the edge partial wrt Mu for pts=[8-15]
   for (int this_vert = 8; this_vert <= 15; this_vert++){
      hex32_partial_mu[this_vert] = 9.0/64.0 
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         *((9.0 * ref_vert[this_vert][2] 
         * (1 -  3.0 * xi_point[2] * xi_point[2]))
         - (2 * xi_point[2]));
   } // end for this_vert

   // calculate the edge partial wrt Mu for pts=[16-23]
   for (int this_vert = 16; this_vert <= 23; this_vert++){
      hex32_partial_mu[this_vert] = 9.0/64.0 
         * (1 - xi_point[0] * xi_point[0])
         * (1 + 9 * xi_point[0] * ref_vert[this_vert][0])
         * (1 + xi_point[1] * ref_vert[this_vert][1])
         * (ref_vert[this_vert][2]);
   } // end for this_vert

   // calculate the edge partial wrt Mu for pts=[24-31]
   for (int this_vert = 24; this_vert <= 31; this_vert++){
      hex32_partial_mu[this_vert] = 9.0/64.0 
         * (1 + xi_point[0] * ref_vert[this_vert][0])
         * (1 - xi_point[1] * xi_point[1])
         * (1 + 9 * xi_point[1] * ref_vert[this_vert][1])
         * (ref_vert[this_vert][2]);
   } // end for this_vert
} // end of partial Mu function

} //end namespace elements
} //end namespace ristra
