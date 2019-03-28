#include <iostream>  // std::cout etc.
#include <cmath>

#include "ristra/elements/elements.h"

namespace ristra {
namespace elements{

// Used by Gauss2/3D to set quadrature points
void LineGaussRuleInfo(
   real_t &x, 
   real_t &w, 
   int &m, 
   int &p){

   m--;
   // creating matrices for weights and points
   real_t g2[2],w3[3],g3[3],w4[4],g4[4],g5[5],w5[5], 
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
   real_t &x, 
   real_t &w, 
   int &m, 
   int &p){

   m--;
   // creating matrices for weights and points
   real_t L2[2],w3[3],L3[3],w4[4],L4[4],L5[5],w5[5], 
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
   vector< vector<real_t> > &these_g_pts,  // gauss points
   vector< vector<real_t> > &these_weights,// gauss weights
   vector<real_t> &tot_g_weight,           // 2D product of gauss weights
   int &quad_order){                       // quadrature order (m)

   int tot_pts = (quad_order*quad_order);    // total quad points in 2D

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j;
      real_t x,w;
 
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
   vector< vector<real_t> > &these_g_pts,   // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   vector<real_t> &tot_g_weight,            // 3D product of gauss weights
   int &quad_order){                        // quadrature order (n)
   
   // total quad points in 3D
   int tot_pts = (quad_order*quad_order*quad_order);  

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j, k, jj;

      real_t x,w;
 
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

// setting gauss quadrature points for 4D elements
void Gauss4D(
   vector< vector<real_t> > &these_g_pts, // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   int &quad_order, // quadrature order (n)
   const int &dim){  // dimension
   
   // total quad points in 3D
   int tot_pts = (quad_order*quad_order*quad_order*quad_order);  

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j, k, l, kk, jj;
      
      real_t x,w;

      real_t a, b, c;

      a = pow(real_t(quad_order), real_t(dim-1.0));
      b = pow(real_t(quad_order), real_t(dim-2.0));
 
      // sets up the i, j, k indices for the line rule implimentation
      int p12 = (quad_order * quad_order);

      l = floor(m/(a)) + 1.0;

      kk = (m + 1) - (a)*(l - 1);

      k=floor((kk - 1)/(b)) + 1;

      jj=(m+1) - ((b)*(k - 1)) - (a)*(l - 1);

      j=floor((jj-1)/quad_order)+1;

      i=jj-quad_order*(j-1);  
      
      these_weights[m]={1.0,1.0,1.0,1.0};
      
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

      // tau direction
      LineGaussRuleInfo(x,w,l,quad_order); // setting pts/weights in l direction
      these_g_pts[m][3]=x; 
      these_weights[m][3]*=w;

          
   } // end for        
   } // end function

// setting Gauss-Lobatto quadrature points for 2D elements
void Lobatto2D(
   vector< vector<real_t> > &these_L_pts, // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   int &quad_order){ // quadrature order (n)

   int tot_pts = (quad_order*quad_order);    // total quad points in 2D

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j;
      real_t x,w;
 
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
   vector< vector<real_t> > &these_L_pts, // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   int &quad_order){  // quadrature order (n)
   
   // total quad points in 3D
   int tot_pts = (quad_order*quad_order*quad_order);  

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j, k, jj;

      real_t x,w;
 
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

// setting gauss quadrature points for 4D elements
void Lobatto4D(
   vector< vector<real_t> > &these_L_pts, // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   int &quad_order, // quadrature order (n)
   const int &dim){  // dimension
   
   // total quad points in 3D
   int tot_pts = (quad_order*quad_order*quad_order*quad_order);  

   //find Gauss-Quadrature Points for volume integration
   for (int m = 0; m < tot_pts; m++) {
      
      int i, j, k, l, kk, jj;
      
      real_t x,w;

      real_t a, b, c;

      a = pow(real_t(quad_order), real_t(dim-1.0)); //to simplify indexing equations
      b = pow(real_t(quad_order), real_t(dim-2.0));
 
      // sets up the i, j, k, l indices for the line rule implimentation

      l = floor(m/(a)) + 1.0;

      kk = (m + 1) - (a)*(l - 1);

      k=floor((kk - 1)/(b)) + 1;

      jj=(m+1) - ((b)*(k - 1)) - (a)*(l - 1);

      j=floor((jj-1)/quad_order)+1;

      i=jj-quad_order*(j-1);  
      
      these_weights[m]={1.0,1.0,1.0,1.0};
      
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

      // tau direction
      LineLobattoRuleInfo(x,w,l,quad_order); // setting pts/weights in l direction
      these_L_pts[m][3]=x; 
      these_weights[m][3]*=w;
          
   } // end for        
   } // end function

//defining the jacobian for 2D/3D elements
void jacobian(
   vector< vector<real_t> > &J_matrix, 
   real_t &det_J,
   const vector< vector<real_t> > &vertices, 
   const vector< vector<real_t> > &this_partial,
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

//defining the jacobian for 4D elements
void jacobian4D(
   vector< vector<real_t> > &J_matrix, 
   real_t &det_J,
   const vector< vector<real_t> > &vertices, 
   const vector< vector<real_t> > &this_partial,
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
    
   det_J =  J_matrix[0][3] * J_matrix[1][2] * J_matrix[2][1] * J_matrix[3][0] 
          - J_matrix[0][2] * J_matrix[1][3] * J_matrix[2][1] * J_matrix[3][0] 
          - J_matrix[0][3] * J_matrix[1][1] * J_matrix[2][2] * J_matrix[3][0] 
          + J_matrix[0][1] * J_matrix[1][3] * J_matrix[2][2] * J_matrix[3][0] 
          + J_matrix[0][2] * J_matrix[1][1] * J_matrix[2][3] * J_matrix[3][0] 
          - J_matrix[0][1] * J_matrix[1][2] * J_matrix[2][3] * J_matrix[3][0] 
          - J_matrix[0][3] * J_matrix[1][2] * J_matrix[2][0] * J_matrix[3][1] 
          + J_matrix[0][2] * J_matrix[1][3] * J_matrix[2][0] * J_matrix[3][1] 
          + J_matrix[0][3] * J_matrix[1][0] * J_matrix[2][2] * J_matrix[3][1] 
          - J_matrix[0][0] * J_matrix[1][3] * J_matrix[2][2] * J_matrix[3][1] 
          - J_matrix[0][2] * J_matrix[1][0] * J_matrix[2][3] * J_matrix[3][1] 
          + J_matrix[0][0] * J_matrix[1][2] * J_matrix[2][3] * J_matrix[3][1] 
          + J_matrix[0][3] * J_matrix[1][1] * J_matrix[2][0] * J_matrix[3][2] 
          - J_matrix[0][1] * J_matrix[1][3] * J_matrix[2][0] * J_matrix[3][2] 
          - J_matrix[0][3] * J_matrix[1][0] * J_matrix[2][1] * J_matrix[3][2] 
          + J_matrix[0][0] * J_matrix[1][3] * J_matrix[2][1] * J_matrix[3][2] 
          + J_matrix[0][1] * J_matrix[1][0] * J_matrix[2][3] * J_matrix[3][2] 
          - J_matrix[0][0] * J_matrix[1][1] * J_matrix[2][3] * J_matrix[3][2] 
          - J_matrix[0][2] * J_matrix[1][1] * J_matrix[2][0] * J_matrix[3][3] 
          + J_matrix[0][1] * J_matrix[1][2] * J_matrix[2][0] * J_matrix[3][3] 
          + J_matrix[0][2] * J_matrix[1][0] * J_matrix[2][1] * J_matrix[3][3] 
          - J_matrix[0][0] * J_matrix[1][2] * J_matrix[2][1] * J_matrix[3][3] 
          - J_matrix[0][1] * J_matrix[1][0] * J_matrix[2][2] * J_matrix[3][3] 
          + J_matrix[0][0] * J_matrix[1][1] * J_matrix[2][2] * J_matrix[3][3];
   
   } // end of jacobian function

//defining the inverse jacobian for 2D element    
void jacobian_inverse_2d(
   vector< vector<real_t> > &J_inverse, 
   const vector< vector<real_t> > &jacobian){

   real_t det = jacobian[0][0]*jacobian[1][1] 
                - jacobian[0][1]*jacobian[1][0];

   J_inverse = {
               {jacobian[1][1]/det, -jacobian[0][1]/det},
               {-jacobian[1][0]/det, jacobian[0][0]/det},
               };
   } // end of 2D jacobin inverse

// defining  the inverse of the Jacobian for 3D elements
void jacobian_inverse_3d(
   vector<vector<real_t> > &J_inverse_matrix,
   const vector<vector<real_t> > &jacobian){

   real_t A_11 = jacobian[1][1]*jacobian[2][2] 
                 - jacobian[1][2]*jacobian[2][1];

   real_t A_22 = jacobian[2][2]*jacobian[0][0] 
                 - jacobian[2][0]*jacobian[0][2];

   real_t A_33 = jacobian[0][0]*jacobian[1][1] 
                 - jacobian[0][1]*jacobian[1][0];

   real_t A_12 = jacobian[1][2]*jacobian[2][0] 
                 - jacobian[1][0]*jacobian[2][2];

   real_t A_23 = jacobian[2][0]*jacobian[0][1] 
                 - jacobian[2][1]*jacobian[0][0];

   real_t A_31 = jacobian[0][1]*jacobian[1][2] 
                 - jacobian[0][2]*jacobian[1][1];

   real_t A_21 = jacobian[2][1]*jacobian[0][2] 
                 - jacobian[0][1]*jacobian[2][2];

   real_t A_32 = jacobian[0][2]*jacobian[1][0] 
                 - jacobian[1][2]*jacobian[0][0];

   real_t A_13 = jacobian[1][0]*jacobian[1][1] 
                 - jacobian[2][0]*jacobian[1][1];
 
   real_t  det = jacobian[0][0]*A_11 + jacobian[0][1]*A_21 
                + jacobian[0][2]*A_31;

   J_inverse_matrix = {
                      {A_11/det, A_12/det, A_13/det},
                      {A_21/det, A_22/det, A_23/det},
                      {A_31/det, A_32/det, A_33/det},
                      };

    } // end of inverse jacobian 

// defining  the inverse of the Jacobian for 4D elements
void jacobian_inverse_4d(
   vector<vector<real_t> > &J_inverse_matrix,
   const vector<vector<real_t> > &jacobian,
   const real_t &det_J){


   real_t inv[16];
   real_t m[16];
   real_t inv_mat[16];

   // convering jacobian into array length 16
   for (int array = 0; array < 4; array++){ 
       m[array] = jacobian[0][array];
   }
   for (int array = 4; array < 8; array++){ 
       m[array] = jacobian[1][array-4];
   }
   for (int array = 8; array < 12; array++){ 
       m[array] = jacobian[2][array-8];
   }
   for (int array = 12; array < 16; array++){ 
       m[array] = jacobian[3][array-12];     
   }


   inv[0] = m[5]  * m[10] * m[15] 
          - m[5]  * m[11] * m[14] 
          - m[9]  * m[6]  * m[15] 
          + m[9]  * m[7]  * m[14] 
          + m[13] * m[6]  * m[11] 
          - m[13] * m[7]  * m[10];

   inv[4] = -m[4]  * m[10] * m[15] 
          + m[4]  * m[11] * m[14] 
          + m[8]  * m[6]  * m[15] 
          - m[8]  * m[7]  * m[14] 
          - m[12] * m[6]  * m[11] 
          + m[12] * m[7]  * m[10];

   inv[8] = m[4]  * m[9] * m[15] 
          - m[4]  * m[11] * m[13] 
          - m[8]  * m[5] * m[15] 
          + m[8]  * m[7] * m[13] 
          + m[12] * m[5] * m[11] 
          - m[12] * m[7] * m[9];

   inv[12] =-m[4]  * m[9] * m[14] 
           + m[4]  * m[10] * m[13] 
           + m[8]  * m[5] * m[14] 
           - m[8]  * m[6] * m[13] 
           - m[12] * m[5] * m[10] 
           + m[12] * m[6] * m[9];

   inv[1] =-m[1]  * m[10] * m[15] 
          + m[1]  * m[11] * m[14] 
          + m[9]  * m[2] * m[15] 
          - m[9]  * m[3] * m[14] 
          - m[13] * m[2] * m[11] 
          + m[13] * m[3] * m[10];

   inv[5] = m[0]  * m[10] * m[15] 
          - m[0]  * m[11] * m[14] 
          - m[8]  * m[2] * m[15] 
          + m[8]  * m[3] * m[14] 
          + m[12] * m[2] * m[11] 
          - m[12] * m[3] * m[10];

   inv[9] =-m[0]  * m[9] * m[15] 
          + m[0]  * m[11] * m[13] 
          + m[8]  * m[1] * m[15] 
          - m[8]  * m[3] * m[13] 
          - m[12] * m[1] * m[11] 
          + m[12] * m[3] * m[9];

   inv[13] = m[0]  * m[9] * m[14] 
           - m[0]  * m[10] * m[13] 
           - m[8]  * m[1] * m[14] 
           + m[8]  * m[2] * m[13] 
           + m[12] * m[1] * m[10] 
           - m[12] * m[2] * m[9];

   inv[2] =  m[1]  * m[6] * m[15] 
           - m[1]  * m[7] * m[14] 
           - m[5]  * m[2] * m[15] 
           + m[5]  * m[3] * m[14] 
           + m[13] * m[2] * m[7] 
           - m[13] * m[3] * m[6];

   inv[6] = -m[0]  * m[6] * m[15] 
           + m[0]  * m[7] * m[14] 
           + m[4]  * m[2] * m[15] 
           - m[4]  * m[3] * m[14] 
           - m[12] * m[2] * m[7] 
           + m[12] * m[3] * m[6];

   inv[10] = m[0]  * m[5] * m[15] 
           - m[0]  * m[7] * m[13] 
           - m[4]  * m[1] * m[15] 
           + m[4]  * m[3] * m[13] 
           + m[12] * m[1] * m[7] 
           - m[12] * m[3] * m[6];

   inv[14] =-m[0]  * m[5] * m[14] 
           + m[0]  * m[6] * m[13] 
           + m[4]  * m[1] * m[14] 
           - m[4]  * m[2] * m[13] 
           - m[12] * m[1] * m[6] 
           + m[12] * m[2] * m[5];

   inv[3] =-m[1] * m[6] * m[11] 
          + m[1] * m[7] * m[10] 
          + m[5] * m[2] * m[11] 
          - m[5] * m[3] * m[10] 
          - m[9] * m[2] * m[7] 
          + m[9] * m[3] * m[6];

   inv[7] =  m[0] * m[6] * m[11] 
           - m[0] * m[7] * m[10] 
           - m[4] * m[2] * m[11] 
           + m[4] * m[3] * m[10] 
           + m[8] * m[2] * m[7] 
           - m[8] * m[3] * m[6];

   inv[11] = -m[0] * m[5] * m[11] 
           +  m[0] * m[7] * m[9] 
           +  m[4] * m[1] * m[11] 
           -  m[4] * m[3] * m[9] 
           -  m[8] * m[1] * m[7] 
           +  m[8] * m[3] * m[5];

   inv[15] = m[0] * m[5] * m[10] 
           - m[0] * m[6] * m[9] 
           - m[4] * m[1] * m[10] 
           + m[4] * m[2] * m[9] 
           + m[8] * m[1] * m[6] 
           - m[8] * m[2] * m[5];

   real_t det_inv = (1.0 / det_J);

   for (int i = 0; i < 16; i++){
      inv_mat[i] = inv[i] * det_inv;
   }
   
   // convering inverse jacobian back to 2D array
   for (int array = 0; array < 4; array++){ 
      J_inverse_matrix[0][array] = inv_mat[array];
   }

   for (int array = 4; array < 8; array++){
      J_inverse_matrix[1][array-4] = inv_mat[array];      
   }

   for (int array = 8; array < 12; array++){
      J_inverse_matrix[2][array-8] = inv_mat[array];    
   }

   for (int array = 12; array < 16; array++){ 
      J_inverse_matrix[3][array-12] = inv_mat[array];          
   }


   } // end of quad point inverse jacobian functions


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

real_t Quad_4_2D::ref_vert[4][2] = // listed as {Xi, Eta}
   {
   {-1.0, -1.0},// 0
   { 1.0, -1.0},// 1
   { 1.0,  1.0},// 2
   {-1.0,  1.0},// 3
   };

// calculate a physical position in an element for a given xi,eta
void Quad_4_2D::physical_position(
   vector <real_t> &x_point, 
   const vector <real_t> &xi_2D_point, 
   const vector< vector<real_t> > &vertices){

   real_t shape_fcn[8];
   real_t check_unity;

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
void Quad_4_2D::basis(
   vector <real_t> &basis,
   const vector <real_t> &xi_2D_point,
   const vector< vector<real_t> > &vertices){

   // calculate the shape functions from each vertex for 0 through 4(xi,eta)
   for( int this_vert = 0; this_vert < 4; this_vert++ ){
      basis[this_vert] = 1.0/4.0
         * (1.0 + xi_2D_point[0]*ref_vert[this_vert][0])
         * (1.0 + xi_2D_point[1]*ref_vert[this_vert][1]);

   }// end for
}// end of quad4 basis functions


// Partial derivative of shape functions with respect to Xi
void  Quad_4_2D::partial_xi_shape_fcn(
   vector<real_t>  &quad4_partial_xi, 
   const vector <real_t> &xi_2D_point) {


   for (int this_vert = 0; this_vert < 4; this_vert++){
      quad4_partial_xi[this_vert] = (1.0/4.0)
         * (ref_vert[this_vert][0])
         * (1.0 + xi_2D_point[1]*ref_vert[this_vert][1]);
   }
}// end of partial xi funciton


// Partial derivative of shape functions with respect to Eta
void  Quad_4_2D::partial_eta_shape_fcn(
   vector<real_t> &quad4_partial_eta, 
   const vector <real_t> &xi_2D_point) {

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

real_t Quad_8_2D::ref_vert[8][2] = // listed as {Xi, Eta}
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
   vector <real_t> &x_point, 
   const vector <real_t> &xi_2D_point, 
   const vector< vector<real_t> > &vertices){
  
   real_t shape_fcn[8];
   real_t check_unity;

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
void Quad_8_2D::basis(
   vector <real_t> &basis,
   const vector <real_t> &xi_2D_point,
   const vector< vector<real_t> > &vertices){

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
   vector<real_t>  &quad8_partial_xi, 
   const vector <real_t> &xi_2D_point) {

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
   vector<real_t> &quad8_partial_eta, 
   const vector <real_t> &xi_2D_point) {

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
      
real_t Quad_12_2D::ref_vert[12][2] = // listed as {Xi, Eta}
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
   vector <real_t> &x_point, 
   const vector <real_t> &xi_point,
   const vector< vector<real_t> > &vertices){
  
   real_t shape_fcn[12];
   real_t check_unity;

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
void Quad_12_2D::basis(
   vector <real_t> &basis,
   const vector <real_t> &xi_2D_point,
   const vector< vector<real_t> > &vertices){

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
   vector<real_t>  &quad12_partial_xi, 
   const vector <real_t> &xi_point) {

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
   vector<real_t> &quad12_partial_eta, 
   const vector <real_t> &xi_point) {

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

real_t Hex8::ref_vert[8][3] = // listed as {Xi, Eta, Mu}
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
   vector <real_t> &x_point,
   const vector <real_t> &xi_point,
   const vector< vector<real_t> > &vertices){

   real_t shape_fcn[8];
   real_t check_unity;

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
void Hex8::basis(
   vector <real_t> &basis,
   const vector <real_t> &xi_point,
   const vector< vector<real_t> > &vertices){

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
   vector<real_t> &hex8_partial_xi, 
   const vector <real_t> &xi_point) {


   for (int this_vert = 0; this_vert < 8; this_vert++){

      hex8_partial_xi[this_vert] = (1.0/8.0)
         * (ref_vert[this_vert][0])
         * (1.0 + xi_point[1]*ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   }   // end for this_vert
} // end of partial Xi function

// with respect to Eta
void Hex8::partial_eta_shape_fcn(
   vector<real_t> &hex8_partial_eta, 
   const vector <real_t> &xi_point) {

   for (int this_vert = 0; this_vert < 8; this_vert++){
      hex8_partial_eta[this_vert] = (1.0/8.0)
         * (1.0 + xi_point[0]*ref_vert[this_vert][0])
         * (ref_vert[this_vert][1])
         * (1.0 + xi_point[2]*ref_vert[this_vert][2]);
   } // end for this_vert
} //end of partial eta function 

// with repsect to Mu
void Hex8::partial_mu_shape_fcn(
   vector<real_t> &hex8_partial_mu, 
   const vector <real_t> &xi_point) {

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

real_t Hex20::ref_vert[20][3] = // listed as {Xi, Eta, Mu}
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
   vector <real_t> &x_point,
   const vector <real_t> &xi_point,
   const vector< vector<real_t> > &vertices){


   real_t shape_fcn[20];
   real_t check_unity;


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
void Hex20::basis(
   vector <real_t> &basis,
   const vector <real_t> &xi_point,
   const vector< vector<real_t> > &vertices){

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
   vector<real_t> &hex20_partial_xi, 
   const vector <real_t> &xi_point) {

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
   vector<real_t> &hex20_partial_eta, 
   const vector <real_t> &xi_point) {

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
   vector<real_t> &hex20_partial_mu, 
   const vector <real_t> &xi_point) {

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


real_t Hex32::ref_vert[32][3] = // listed as {Xi, Eta, Mu}
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
   vector <real_t> &x_point,
   const vector <real_t> &xi_point,
   const vector< vector<real_t> > &vertices){

   real_t shape_fcn[32];
   real_t check_unity;


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
void Hex32::basis(
   vector <real_t> &basis,
   const vector <real_t> &xi_point,
   const vector< vector<real_t> > &vertices){

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
   vector<real_t> &hex32_partial_xi, 
   const vector <real_t> &xi_point) {

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
   vector<real_t> &hex32_partial_eta, 
   const vector <real_t> &xi_point) {

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
   vector<real_t> &hex32_partial_mu, 
   const vector <real_t> &xi_point) {

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

/*

 ==========================
  Arbitrary Order Elements
 ==========================


  / __ \                | | \ | |
 | |  | |_   _  __ _  __| |  \| |
 | |  | | | | |/ _` |/ _` | . ` |
 | |__| | |_| | (_| | (_| | |\  |
  \___\_\\__,_|\__,_|\__,_|_| \_| 

representative linear element for visualization
   
         Eta
          ^
          |
  3--------------2
  |       |      |
  |       |      |
  |       |      |
  |       |      |
  |       +------|-----> Xi   
  |              |
  |              |
  |              |
  0--------------1
    

*/

// creates nodal positions with Chebyshev spacing
void QuadN::chebyshev_nodes_1D(
   vector<real_t> &cheb_nodes_1D,  // Chebyshev nodes
   const int &order){              // Interpolation order
   
   real_t pi = 3.14159265358979323846;
   
   // loop to build the base set of Chebyshev nodes
   for (int i = 1; i < order + 1; i++){
      cheb_nodes_1D[i - 1] = -cos(pi*(2.0*i - 1.0)/(2.0*(order + 1.0)));
   } // end for i
   
   //replacing the first and last index with the element boundary 
   cheb_nodes_1D[0] = -1.0;
   cheb_nodes_1D[order] = 1.0;
}

// Lagrange Interp in 1D, returns interpolants and derivative
// works with any nodal spacing
void QuadN::lagrange_1D(
   vector <real_t> &interp,            // interpolant
   vector <real_t> &Dinterp,           // derivative of function
   const real_t &x_point,              // point of interest in element
   const vector <real_t> &xi_point,    // nodal positions in 1D, normally chebyshev
   const int &orderN){                 // order of element
   
   vector <real_t> num(orderN + 1);     // numerator of interpolant
   vector <real_t> denom(orderN + 1);   // denomenator of interpolant
   real_t q = 0.0;
   
   for(int i = 0; i < orderN + 1; i++){ // looping over the nodes
      real_t n = 1.0;         // placeholder numerator
      real_t d = 1.0;         // placeholder denominator
      real_t c = 1.0;         // placeholder value of n/d
      real_t p = 0.0;         // placeholder for derivative values
      real_t s = 1.0;
      for(int j = 0; j < orderN + 1; j++){  // looping over the nodes !=i

         if (j != i ){
            n = n*(x_point - xi_point[j]);
            d = d*(xi_point[i] - xi_point[j]);
            
            real_t s = 1.0;
            for(int N = 0; N < orderN + 1; N++){  // looping over the nodes !=i
               if (N != j && N != i ){
                  
                  s = s * (x_point - xi_point[N]);
                  
               }// end if
            }//end for
            p += s; 

         }//end if
         
         c = n/d; // storing a single value for interpolation for node i
         q = (p/d); // storing the derivative of the interpolating function
      } // end looping over nodes != i

      // writing value to vectors for later use
      interp[i]   = c;     // Interpolant value at given point
      Dinterp[i]  = q;     // derivative of each function

   } // end loop over all nodes
} // end of Legrange_1D function

// Corners of Lagrange element for mapping
void QuadN::corners (
   vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements 
   vector< vector<real_t> > &lag_corner,  // corner nodes of QuadN element
   const int &orderN){                    // Element order


   /*
   This image represents the corner mapping notation of an arbitrary ordered
   Lagrange element. The corner function takes in the element order and nodal positions and
   returns a vector containing the indices of the corner in alphabetical order.

        Eta
         ^
         |
  C------+-----D
  |      |     |
  |      |     |
  |      |     |
  |      ------+------> Xi   
  |            |
  |            |
  A------------B

   */
   int N = orderN + 1;      //number of nodes in each direction

   int A = 0;                      
   int B = N - 1.0;                 
   int C = (N*N) - N;         
   int D = (N*N)-1.0;               



   lag_corner[0] = lag_nodes[A];
   std::cout<<"Corner A = "<<lag_corner[0][0] << "  "<<lag_corner[0][1] <<std::endl;

   lag_corner[1] = lag_nodes[B];
   std::cout<<"Corner B = "<<lag_corner[1][0] << "  "<<lag_corner[1][1] <<std::endl;

   lag_corner[2] = lag_nodes[C];
   std::cout<<"Corner C = "<<lag_corner[2][0] << "  "<<lag_corner[2][1] <<std::endl;

   lag_corner[3] = lag_nodes[D];
   std::cout<<"Corner D = "<<lag_corner[3][0] << "  "<<lag_corner[3][1] <<std::endl;
}// end of corner mapping function

// Functions for mapping reference position to physical position for any 
// point in an arbitrary order 3D lagrange element
void QuadN::physical_position (
   vector <real_t> &x_point,                    // location in real space
   const vector< vector<real_t> > &lag_nodes_2d,   // Nodes of Lagrange elements 
   const vector <real_t> &lag_basis_2d,         // 3D basis values 
   const int &orderN){                          // order of the element


   int nodes = orderN + 1;
   int numnodes_2d = nodes * nodes;

   for (int this_vert = 0; this_vert < numnodes_2d; this_vert++ ){
      for (int dim = 0; dim < 1; dim++){
         x_point[dim] += lag_nodes_2d[this_vert][dim]*lag_basis_2d[this_vert];
      } // end for dim
   } // end for this_vert
}// end physical position function

void QuadN::basis_partials (
   vector< vector<real_t> > &lag_nodes_2d,// Nodes of Lagrange elements (to be filled in)
   vector <real_t> &nodes_1d,             // Nodal spacing in 1D, any spacing is accepted
   vector <real_t> &val_1d,               // Interpolant Value in 1D
   vector <real_t> &DVal_1d,              // Derivateive of basis in 1D
   vector< vector<real_t> >  &val_2d,     // for holding the interpolant in each direction
   vector< vector<real_t> >  &DVal_2d,    // for holding the derivatives in each direction
   vector <real_t> &lag_basis_2d,         // 3D basis values 
   vector< vector<real_t> > &lag_partial, // Partial of basis 
   const vector <real_t> &xi_point,       // point of interest
   const int &orderN){                    // Element order

   /*

   representative linear element for visualization
   
            j
            |     k    
            |    /
            |   /
        6---+----7
       /|   |   /|
      / |   |  / |
     2--------3  |
     |  |    -|--+---> i
     |  |     |  |
     |  4-----|--5
     | /      | /       
     |/       |/
     0--------1
    
   Note: left hand coordinate coordinates
   */

   int N = orderN + 1;      //number of nodes in each direction
   int tot_pts = (N*N);     // total nodes in 2D
   
   real_t sumi = 0.0;
   real_t sumj = 0.0;



   //Setting nodes for Lagrange Elements
   for (int m = 0; m < tot_pts; m++) {

      int i, j;



      // sets up the i and j indices for the nodes of an 


      j = floor(m/N)+1; 
      i = (m+1) - N*(j-1);

      // xi direction
      lag_nodes_2d[m][0] = nodes_1d[i-1]; 

      // eta direction
      lag_nodes_2d[m][1] = nodes_1d[j-1]; 


   // calling function to assign nodal values for basis and derivative

      //evaluating Lagrange interpolants for each function at xi_point

      lagrange_1D(val_1d, DVal_1d, xi_point[0], nodes_1d, orderN);
      val_2d[m][0]  = val_1d[i-1]; 
      DVal_2d[m][0] = DVal_1d[i-1];

      // resetting to zero
      for(int i = 0.0; i < N; i++){
         val_1d[i]  = 0.0;
         DVal_1d[i] = 0.0;
      }


      //evaluating Legrange interpolants for each function at xi_point

      lagrange_1D(val_1d, DVal_1d, xi_point[1], nodes_1d, orderN);
      val_2d[m][1]  = val_1d[j-1]; 
      DVal_2d[m][1] = DVal_1d[j-1];

      // resetting to zero
      for(int i = 0.0; i < N; i++){
         val_1d[i]  = 0.0;
         DVal_1d[i] = 0.0;
      }


   // Assigning and storing the Basis
      lag_basis_2d[m] = val_2d[m][0] * val_2d[m][1];

   // Assigning and storing the partials

      lag_partial[m][0]  = DVal_2d[m][0] * val_2d[m][1];
      lag_partial[m][1]  = val_2d[m][0] * DVal_2d[m][1];

   } // end for  
}// end basis_partials function




/*
  _   _           _   _ 
 | | | | _____  _| \ | |
 | |_| |/ _ \ \/ /  \| |
 |  _  |  __/>  <| |\  |
 |_| |_|\___/_/\_\_| \_|
                        
representative linear element for visualization
   
            j
            |     k    
            |    /
            |   /
        6---+----7
       /|   |   /|
      / |   |  / |
     2--------3  |
     |  |    -|--+---> i
     |  |     |  |
     |  4-----|--5
     | /      | /       
     |/       |/
     0--------1
    
   Note: left hand coordinate coordinates

*/

// creates nodal positions with Chebyshev spacing
void HexN::chebyshev_nodes_1D(
   vector<real_t> &cheb_nodes_1D,  // Chebyshev nodes
   const int &order){              // Interpolation order
   
   real_t pi = 3.14159265358979323846;
   
   // loop to build the base set of Chebyshev nodes
   for (int i = 1; i < order + 1; i++){
      cheb_nodes_1D[i - 1] = -cos(pi*(2.0*i - 1.0)/(2.0*(order + 1.0)));
   } // end for i
   
   //replacing the first and last index with the element boundary 
   cheb_nodes_1D[0] = -1.0;
   cheb_nodes_1D[order] = 1.0;
}

// Lagrange Interp in 1D, returns interpolants and derivative
// works with any nodal spacing
void HexN::lagrange_1D(
   vector <real_t> &interp,            // interpolant
   vector <real_t> &Dinterp,           // derivative of function
   const real_t &x_point,              // point of interest in element
   const vector <real_t> &xi_point,    // nodal positions in 1D, normally chebyshev
   const int &orderN){                 // order of element
   
   vector <real_t> num(orderN + 1);     // numerator of interpolant
   vector <real_t> denom(orderN + 1);   // denomenator of interpolant
   real_t q = 0.0;
   
   for(int i = 0; i < orderN + 1; i++){ // looping over the nodes
      real_t n = 1.0;         // placeholder numerator
      real_t d = 1.0;         // placeholder denominator
      real_t c = 1.0;         // placeholder value of n/d
      real_t p = 0.0;         // placeholder for derivative values
      real_t s = 1.0;
      for(int j = 0; j < orderN + 1; j++){  // looping over the nodes !=i

         if (j != i ){
            n = n*(x_point - xi_point[j]);
            d = d*(xi_point[i] - xi_point[j]);
            
            real_t s = 1.0;
            for(int N = 0; N < orderN + 1; N++){  // looping over the nodes !=i
               if (N != j && N != i ){
                  
                  s = s * (x_point - xi_point[N]);
                  
               }// end if
            }//end for
            p += s; 

         }//end if
         
         c = n/d; // storing a single value for interpolation for node i
         q = (p/d); // storing the derivative of the interpolating function
      } // end looping over nodes != i

      // writing value to vectors for later use
      interp[i]   = c;     // Interpolant value at given point
      Dinterp[i]  = q;     // derivative of each function

   } // end loop over all nodes
} // end of Legrange_1D function

// Corners of Lagrange element for mapping
void HexN::corners (
   vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements 
   vector< vector<real_t> > &lag_corner,  // corner nodes of HexN element
   const int &orderN){                    // Element order


   /*
   This image represents the corner mapping notation of an arbitrary ordered
   Lagrange element. The corner function takes in the element order and nodal positions and
   returns a vector containing the indices of the corner in alphabetical order.

           j
           |     k    
           |    /
           |   /
       G---+----H
      /|   |   /|
     / |   |  / |
    C--------D  |
    |  |    -|--+---> i
    |  |     |  |
    |  E-----|--F
    | /      | /       
    |/       |/
    A--------B
   
   Note: left hand coordinate coordinates
   */
   int N = orderN + 1;      //number of nodes in each direction

   int A = 0;                      
   int B = N - 1.0;                 
   int C = (N*N) - N;         
   int D = (N*N)-1.0;               
   int E = (N*N*N) - (N*N) ;  
   int F = (N*N*N) - (N*N) + N - 1.0;  
   int G = (N*N*N) - (N);     
   int H = (N*N*N) - 1; 


   lag_corner[0] = lag_nodes[A];
   std::cout<<"Corner A = "<<lag_corner[0][0] << "  "<<lag_corner[0][1] << "  "<<lag_corner[0][2] <<std::endl;

   lag_corner[1] = lag_nodes[B];
   std::cout<<"Corner B = "<<lag_corner[1][0] << "  "<<lag_corner[1][1] << "  "<<lag_corner[1][2] <<std::endl;

   lag_corner[2] = lag_nodes[C];
   std::cout<<"Corner C = "<<lag_corner[2][0] << "  "<<lag_corner[2][1] << "  "<<lag_corner[2][2] <<std::endl;

   lag_corner[3] = lag_nodes[D];
   std::cout<<"Corner D = "<<lag_corner[3][0] << "  "<<lag_corner[3][1] << "  "<<lag_corner[3][2] <<std::endl;

   lag_corner[4] = lag_nodes[E];
   std::cout<<"Corner E = "<<lag_corner[4][0] << "  "<<lag_corner[4][1] << "  "<<lag_corner[4][2] <<std::endl;

   lag_corner[5] = lag_nodes[F];
   std::cout<<"Corner F = "<<lag_corner[5][0] << "  "<<lag_corner[5][1] << "  "<<lag_corner[5][2] <<std::endl;

   lag_corner[6] = lag_nodes[G];
   std::cout<<"Corner G = "<<lag_corner[6][0] << "  "<<lag_corner[6][1] << "  "<<lag_corner[6][2] <<std::endl;

   lag_corner[7] = lag_nodes[H];
   std::cout<<"Corner H = "<<lag_corner[7][0] << "  "<<lag_corner[7][1] << "  "<<lag_corner[7][2] <<std::endl;
}// end of corner mapping function

// Functions for mapping reference position to physical position for any 
// point in an arbitrary order 3D lagrange element
void HexN::physical_position (
   vector <real_t> &x_point,                    // location in real space
   const vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements 
   const vector <real_t> &lag_basis_3d,         // 3D basis values 
   const int &orderN){                          // order of the element


   int nodes = orderN + 1;
   int numnodes_3d = nodes * nodes * nodes;

   for (int this_vert = 0; this_vert < numnodes_3d; this_vert++ ){
      for (int dim = 0; dim < 2; dim++){
         x_point[dim] += lag_nodes[this_vert][dim]*lag_basis_3d[this_vert];
      } // end for dim
   } // end for this_vert
}// end physical position function

void HexN::basis_partials (
   vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements (to be filled in)
   vector <real_t> &nodes_1d,             // Nodal spacing in 1D, any spacing is accepted
   vector <real_t> &val_1d,               // Interpolant Value in 1D
   vector <real_t> &DVal_1d,              // Derivateive of basis in 1D
   vector< vector<real_t> >  &val_3d,     // for holding the interpolant in each direction
   vector< vector<real_t> >  &DVal_3d,    // for holding the derivatives in each direction
   vector <real_t> &lag_basis_3d,         // 3D basis values 
   vector< vector<real_t> > &lag_partial, // Partial of basis 
   const vector <real_t> &xi_point,       // point of interest
   const int &orderN){                    // Element order

   /*

   representative linear element for visualization
   
            j
            |     k    
            |    /
            |   /
        6---+----7
       /|   |   /|
      / |   |  / |
     2--------3  |
     |  |    -|--+---> i
     |  |     |  |
     |  4-----|--5
     | /      | /       
     |/       |/
     0--------1
    
   Note: left hand coordinate coordinates
   */

   int N = orderN + 1;      //number of nodes in each direction
   int tot_pts = (N*N*N);  // total nodes in 3D
   
   real_t sumi = 0.0;
   real_t sumj = 0.0;
   real_t sumk = 0.0;


   //Setting nodes for Lagrange Elements
   for (int m = 0; m < tot_pts; m++) {

      int i, j, k, jj;



      // sets up the i, j, k indices for the nodes of an 
      // arbitrary order lagrange element
      int p12 = (N * N);

      k  = floor(m/p12) + 1; 

      jj = (m+1) - p12 * (k-1); 
      j  = floor((jj-1) / N)+1;

      i  = jj - N * (j-1); 

      // xi direction
      lag_nodes[m][0] = nodes_1d[i-1]; 

      // eta direction
      lag_nodes[m][1] = nodes_1d[j-1]; 

      // mu direction 
      lag_nodes[m][2] = nodes_1d[k-1]; 

   // calling function to assign nodal values for basis and derivative

      //evaluating Lagrange interpolants for each function at xi_point

      lagrange_1D(val_1d, DVal_1d, xi_point[0], nodes_1d, orderN);
      val_3d[m][0]  = val_1d[i-1]; 
      DVal_3d[m][0] = DVal_1d[i-1];

      // resetting to zero
      for(int i = 0.0; i < N; i++){
         val_1d[i]  = 0.0;
         DVal_1d[i] = 0.0;
      }


      //evaluating Legrange interpolants for each function at xi_point

      lagrange_1D(val_1d, DVal_1d, xi_point[1], nodes_1d, orderN);
      val_3d[m][1]  = val_1d[j-1]; 
      DVal_3d[m][1] = DVal_1d[j-1];

      // resetting to zero
      for(int i = 0.0; i < N; i++){
         val_1d[i]  = 0.0;
         DVal_1d[i] = 0.0;
      }

      //evaluating Legrange interpolants for each function at xi_point

      lagrange_1D(val_1d, DVal_1d, xi_point[2], nodes_1d, orderN);
      val_3d[m][2]  = val_1d[k-1];   //3d[2dto1d(m, 2)]
      DVal_3d[m][2] = DVal_1d[k-1];
      // resetting to zero
      for(int i = 0.0; i < N; i++){
         val_1d[i]  = 0.0;
         DVal_1d[i] = 0.0;
      }


   // Assigning and storing the Basis
      lag_basis_3d[m] = val_3d[m][0] * val_3d[m][1] * val_3d[m][2];

   // Assigning and storing the partials

      lag_partial[m][0]  = DVal_3d[m][0] * val_3d[m][1] * val_3d[m][2];
      lag_partial[m][1]  = val_3d[m][0] * DVal_3d[m][1] * val_3d[m][2];
      lag_partial[m][2]  = val_3d[m][0] * val_3d[m][1] * DVal_3d[m][2];


   } // end for  
}// end basis_partials function




/*
 ==========================
  4D Tesseract element
 ==========================
 
 The finite element local point numbering for a 16 node Tesseract is
 based on the 3D Hex8 Ensight element
 

                 _.15-------------------------------------14
            _.+<    |\                              . >-"/ |
      _ .+>         | \                         .>"" ./    |
  .>""              |  \                     <""    /      |
12----------------------+------------------13    ./        |
| )<=               |    \               / | _/""          |
|     )\+           |     \            / /"|               |
|         (\=       |   _. 7---------+--6  |               |
|             \>   .|+<    |       / . "|  |               |
|               '4--+------+------5'    |  |               |
|                |  |      |      |     |  |               |
|                |  |      |      |     |  |               |
|                |  |      |      |     |  |               |
|                |  |      |      |     |  |               |
|                |  |      |      |     |  |               |
|                |  |      |      |     |  |               |
|                |  |   _ .3------+-----2_ |               |
|                |  | "   /       |   /'  '| \= _          |
|                0--+---+---------1*"      |     ""\       |
|             ./'   |  "           \       |         "">   |
|            /      |/              \      |             ".|
|         /        11----------------+-----+--------------10
|      ./    .+<""                    )    |           .</
|    /(   /(                            \  |     _.+</
| ./  /"                                 \ |  >(
8------------------------------------------9'

              j
              ^        k
              |      /
              |    / 
              |  /
              |/
              +---------->i

   i = Xi
   j = Eta
   k = Mu
   t = Tau 


 Note: left hand coordinate coordinates
 */


int  num_nodes = 16;

real_t ref_vert[16][4] = // listed as {Xi, Eta, Mu, Tau}
   {
   // Interior cube bottom
   {-1.0, -1.0, -1.0, -1.0},//0
   {+1.0, -1.0, -1.0, -1.0},//1
   {+1.0, -1.0, +1.0, -1.0},//2
   {-1.0, -1.0, +1.0, -1.0},//3
   // Interior cube top
   {-1.0, +1.0, -1.0, -1.0},//4
   {+1.0, +1.0, -1.0, -1.0},//5
   {+1.0, +1.0, +1.0, -1.0},//6
   {-1.0, +1.0, +1.0, -1.0},//7
   // Exterior cube bottom
   {-1.0, -1.0, -1.0, +1.0},//8
   {+1.0, -1.0, -1.0, +1.0},//9
   {+1.0, -1.0, +1.0, +1.0},//10
   {-1.0, -1.0, +1.0, +1.0},//11
   // Exterior cube top
   {-1.0, +1.0, -1.0, +1.0},//12
   {+1.0, +1.0, -1.0, +1.0},//13
   {+1.0, +1.0, +1.0, +1.0},//14
   {-1.0, +1.0, +1.0, +1.0},//15
   };



// calculate a physical position in an element for a given xi,eta,mu
void Tess16::physical_position(
   vector <real_t> &x_point,
   const vector <real_t> &xi_point,
   const vector< vector<real_t> > &vertices){

   real_t shape_fcn[16];
   real_t check_unity;
   real_t sum = 0;
   
   // calculate the shape functions from each vertex for (xi,eta,mu, tau)
   for(int this_vert = 0; this_vert < 16; this_vert++){
      shape_fcn[this_vert] = 1.0/16.0
                  * (1 + xi_point[0]*ref_vert[this_vert][0]) 
                  * (1 + xi_point[1]*ref_vert[this_vert][1]) 
                  * (1 + xi_point[2]*ref_vert[this_vert][2]) 
                  * (1 + xi_point[3]*ref_vert[this_vert][3]);
   } // end for shape functions

   // calculate the position in physical space
   for (int dim = 0; dim < 4; dim++)
      x_point[dim] = 0.0;

   check_unity = 0.0;
   for (int this_vert = 0; this_vert < 16; this_vert++ ){
      
      for (int dim = 0; dim < 4; dim++){
         x_point[dim] += vertices[this_vert][dim]*shape_fcn[this_vert];
      } // end for dim
   
      // check partition of unity
      check_unity += shape_fcn[this_vert];
   } // end for this_vert
    
   // unit test
   // std::cout << "Tess 16 partion of unity :" << check_unity << std::endl;
} // End physical position function


// Partial derivative of shape functions with respect to Xi at Xi_point
void Tess16::partial_xi_shape_fcn(
   vector<real_t>  &tess16_partial_xi, 
   const vector <real_t> &xi_point) {

   for (int this_vert = 0; this_vert < 16; this_vert++){

      tess16_partial_xi[this_vert] = 1.0/16.0
                                     * (ref_vert[this_vert][0])
                                     * (1 + xi_point[1]*ref_vert[this_vert][1])
                                     * (1 + xi_point[2]*ref_vert[this_vert][2])
                                     * (1 + xi_point[3]*ref_vert[this_vert][3]);
   }   // end for this_vert 
} // end partial Xi function

// Partial derivative of shape functions with respect to Eta
void Tess16::partial_eta_shape_fcn(
   vector<real_t> &tess16_partial_eta, 
   const vector <real_t> &xi_point) {

   for (int this_vert = 0; this_vert < 16; this_vert++){  
      tess16_partial_eta[this_vert] = 1.0/16.0
                                    * (1 + xi_point[0]*ref_vert[this_vert][0])
                                    * (ref_vert[this_vert][1])
                                    * (1 + xi_point[2]*ref_vert[this_vert][2])
                                    * (1 + xi_point[3]*ref_vert[this_vert][3]);
                                     
   }   // end for this_vert 
}  // End partial eta function

// Partial derivative of shape functions with respect to Mu
void Tess16::partial_mu_shape_fcn(
   vector<real_t> &tess16_partial_mu, 
   const vector <real_t> &xi_point) {

    for (int this_vert = 0; this_vert < 16; this_vert++){  
      tess16_partial_mu[this_vert] = 1.0/16.0
                                     * (1 + xi_point[0]*ref_vert[this_vert][0])
                                     * (1 + xi_point[1]*ref_vert[this_vert][1])
                                     * (ref_vert[this_vert][2])
                                     * (1 + xi_point[3]*ref_vert[this_vert][3]);

   } // end for this_vert   
} // end partial Mu fuction

// Partial derivative of shape functions with respect to Tau
void Tess16::partial_tau_shape_fcn(
   vector<real_t> &tess16_partial_tau, 
   const vector <real_t> &xi_point) {

   for (int this_vert = 0; this_vert < 16; this_vert++){  
      tess16_partial_tau[this_vert] = 1.0/16.0
                                     * (1 + xi_point[0]*ref_vert[this_vert][0])
                                     * (1 + xi_point[1]*ref_vert[this_vert][1])
                                     * (1 + xi_point[2]*ref_vert[this_vert][2])
                                     * (ref_vert[this_vert][3]);
                                     

   } // end for this_vert    
} // End partial tau function


} //end namespace elements
} //end namespace ristra
