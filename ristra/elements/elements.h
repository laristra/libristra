#ifndef ELEMENTS_H
#define ELEMENTS_H 

#include <iostream>

#include "ristra/elements/utilities.h"

namespace ristra{
namespace elements{

// Used by Gauss2/3D to set quadrature points
void LineGaussRuleInfo(
   double &x, double &w, 
   int &m,  int &p);

// Used by Lovatto 1D/2D to set Lobatto quadrature points
void LineLobattoRuleInfo(
   double &x, 
   double &w, 
   int &m, 
   int &p); // end of Lobatto line rule function      

// setting gauss quadrature points for 2D elements
void Gauss2D(
   std::vector< std::vector<double> > &these_g_pts,  // gauss points
   std::vector< std::vector<double> > &these_weights,// gauss weights
   std::vector<double> &tot_g_weight,           // 2D product of gauss weights
   int &quad_order);                       // quadrature order (m)

// setting gauss quadrature points for 2D elements
void Gauss3D(
   std::vector< std::vector<double> > &these_g_pts,   // gauss points
   std::vector< std::vector<double> > &these_weights, // gauss weights
   std::vector<double> &tot_g_weight,            // 3D product of gauss weights
   int &quad_order);                        // quadrature order (n)

// setting Gauss-Lobatto quadrature points for 2D elements
void Lobatto2D(
   vector< vector<double> > &these_L_pts, // gauss points
   vector< vector<double> > &these_weights, // gauss weights
   int &quad_order); // quadrature order (n)

// setting Gauss-Lobatto quadrature points for 3D elements
void Lobatto3D(
   vector< vector<double> > &these_L_pts, // gauss points
   vector< vector<double> > &these_weights, // gauss weights
   int &quad_order); 

//defining the jacobian for 2D/3D elements
void jacobian(
   std::vector< std::vector<double> > &J_matrix, 
   double &det_J,
   const std::vector< std::vector<double> > &vertices, 
   const std::vector< std::vector<double> > &this_partial,
   const int &num_nodes,
   const int &dim);

//defining the inverse jacobian for 2D element    
void jacobian_inverse_2d(
   std::vector< std::vector<double> > &J_inverse, 
   const std::vector< std::vector<double> > &jacobian);

//defining the inverse jacobian for 2D element    
void jacobian_inverse_3d(
   std::vector<std::vector<double> > &J_inverse_matrix,
   const std::vector<std::vector<double> > &jacobian);

class Element2D {
 
   public:


      // calculate a physical position in an element for a given xi,eta
      virtual void physical_position(vector <double> &x_2D_point,
                                    const vector <double> &xi_2D_point,
                                    const vector< vector<double> > &vertices) = 0;

      // calculate the value for the basis at each node for a given xi,eta
      virtual void basis(vector <double> &basis,
                         const vector <double> &xi_2D_point,
                         const vector< vector<double> > &vertices) = 0;

      // Partial derivative of shape functions with respect to Xi
      virtual void  partial_xi_shape_fcn(vector<double>  &partial_xi, 
                                         const vector <double> &xi_2D_point) = 0;

   
      // Partial derivative of shape functions with respect to Xi
      virtual void  partial_eta_shape_fcn(vector<double> &partial_eta, 
                                          const vector <double> &xi_2D_point) = 0;
}; // end of 2D element class

class Element3D {

   public:
   
      // calculate the volume of an element
      //virtual double volume(const vector< vector<double> > &vertices);
   
      // calculate a physical position in an element for a given xi,eta,mu
      virtual void physical_position(vector <double> &x_point,
                                     const vector <double> &xi_point,
                                     const vector< vector<double> > &vertices) = 0;

      // calculate the value for the basis at each node for a given xi,eta, mu
      virtual void basis(vector <double> &basis,
                         const vector <double> &xi_point,
                         const vector< vector<double> > &vertices) = 0;

      // Partial derivative of shape functions with respect to Xi at Xi_point
      virtual void partial_xi_shape_fcn(vector<double>  &partial_xi, 
                                        const vector <double> &xi_point) = 0;

      // Partial derivative of shape functions with respect to Eta
      virtual void partial_eta_shape_fcn(vector<double> &partial_eta, 
                                         const vector <double> &xi_point) = 0;

      // Partial derivative of shape functions with respect to Mu
      virtual void partial_mu_shape_fcn(vector<double> &partial_mu, 
                                        const vector <double> &xi_point) = 0;
}; // end of 3D parent class


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
class Quad_4_2D: public Element2D {
   protected:

     static double ref_vert[4][2]; // listed as {Xi, Eta}



   public:

      // calculate a physical position in an element for a given xi,eta
      void physical_position(vector <double> &x_point, 
                             const vector <double> &xi_2D_point, 
                             const vector< vector<double> > &vertices);
  
         double shape_fcn[4];
         double check_unity;

      // calculate the value for the basis at each node for a given xi,eta
      void basis(vector <double> &basis,
                 const vector <double> &xi_2D_point,
                 const vector< vector<double> > &vertices);

      // Partial derivative of shape functions with respect to Xi
      void  partial_xi_shape_fcn(vector<double>  &quad4_partial_xi, 
                                 const vector <double> &xi_2D_point);


      // Partial derivative of shape functions with respect to Eta
      void  partial_eta_shape_fcn(vector<double> &quad4_partial_eta, 
                                  const vector <double> &xi_2D_point);
}; // end of quad_4_2D class

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
class Quad_8_2D: public Element2D {

   
   public:

      static double ref_vert[8][2];  // listed as {Xi, Eta}


      // calculate a physical position in an element for a given xi,eta,
      void physical_position(
               vector <double> &x_point, 
               const vector <double> &xi_2D_point, 
               const vector< vector<double> > &vertices);
  
         double shape_fcn[8];
         double check_unity;

      // calculate the value for the basis at each node for a given xi,eta
      void basis(vector <double> &basis,
                 const vector <double> &xi_2D_point,
                 const vector< vector<double> > &vertices); 

      // Partial derivative of shape functions with respect to Xi
      void partial_xi_shape_fcn(vector<double>  &quad8_partial_xi, 
                                 const vector <double> &xi_2D_point);

      // Partial derivative of shape functions with respect to Eta
      void partial_eta_shape_fcn(vector<double> &quad8_partial_eta, 
                                 const vector <double> &xi_2D_point);
}; // end of quad8 class

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
class Quad_12_2D: public Element2D {
   public:

      static double ref_vert[12][2];  // listed as {Xi, Eta}
        
      // calculate a physical position in an element for a given xi,eta,
      void physical_position(
               vector <double> &x_point, 
               const vector <double> &xi_point,
               const vector< vector<double> > &vertices);
  
         double shape_fcn[12];
         double check_unity;

      // calculate the value for the basis at each node for a given xi,eta
      void basis(vector <double> &basis,
                 const vector <double> &xi_2D_point,
                 const vector< vector<double> > &vertices);

      // Partial derivative of shape functions with respect to Xi
      void partial_xi_shape_fcn(vector<double>  &quad12_partial_xi, 
                                const vector <double> &xi_point);

      // Partial derivative of shape functions with respect to Eta
      void partial_eta_shape_fcn(vector<double> &quad12_partial_eta, 
                                 const vector <double> &xi_point);
}; // end of quad12 class


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
class Hex8: public Element3D {
   protected:

      static double ref_vert[8][3];  // listed as {Xi, Eta, Mu}

   public:

      // get the physical location for a given xi_point
      void physical_position (vector <double> &x_point,
                              const vector <double> &xi_point,
                              const vector< vector<double> > &vertices);
         int    dim;
         
         double shape_fcn[8];
         double check_unity;
      
      // calculate the value for the basis at each node for a given xi,eta, mu
      void basis(vector <double> &basis,
                 const vector <double> &xi_point,
                 const vector< vector<double> > &vertices);

      // calculate the partials of the shape function 
      // with respect to Xi
      void partial_xi_shape_fcn(vector<double> &hex8_partial_xi, 
                                const vector <double> &xi_point);

      // with respect to Eta
      void partial_eta_shape_fcn(vector<double> &hex8_partial_eta, 
                                 const vector <double> &xi_point);

      // with repsect to Mu
      void partial_mu_shape_fcn(vector<double> &hex8_partial_mu, 
                                const vector <double> &xi_point);
}; // end of hex 8 class

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
class Hex20: public Element3D {
   

   public:

    static double ref_vert[20][3]; // listed as {Xi, Eta, Mu}

      // get the physical location for a given xi_point
      void physical_position (vector <double> &x_point,
                              const vector <double> &xi_point,
                              const vector< vector<double> > &vertices);
      
         int    this_vert;
         int    dim;
      
         double shape_fcn[20];
         double check_unity;
     
      // calculate the value for the basis at each node for a given xi,eta, mu
      void basis(vector <double> &basis,
                 const vector <double> &xi_point,
                 const vector< vector<double> > &vertices);

      // Calculate the partials of the shape functions
      // with respect to Xi
      void  partial_xi_shape_fcn(vector<double> &hex20_partial_xi, 
                                 const vector <double> &xi_point);

      // with respect to Eta
      void partial_eta_shape_fcn(vector<double> &hex20_partial_eta, 
                                 const vector <double> &xi_point);
      // with repsect to mu
      void partial_mu_shape_fcn(vector<double> &hex20_partial_mu, 
                                const vector <double> &xi_point);
}; //end of 20 node element class



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
class Hex32: public Element3D {
   
         
   public:

      static  double ref_vert[32][3]; // listed as {Xi, Eta, Mu}
 
      // get the physical location for a given xi_point
      void physical_position (vector <double> &x_point,
                             const vector <double> &xi_point,
                             const vector< vector<double> > &vertices);

         int    dim;
      
         double shape_fcn[32];
         double check_unity;

      // calculate the value for the basis at each node for a given xi,eta, mu
      void basis(vector <double> &basis,
                 const vector <double> &xi_point,
                 const vector< vector<double> > &vertices);
      
      // Calculate the partials of the shape functions
      // with respect to Xi
      void  partial_xi_shape_fcn(vector<double> &hex32_partial_xi, 
                                 const vector <double> &xi_point);

      // with respect to Eta
      void partial_eta_shape_fcn(vector<double> &hex32_partial_eta, 
                                 const vector <double> &xi_point);
      // with repsect to mu
      void partial_mu_shape_fcn(vector<double> &hex32_partial_mu, 
                                const vector <double> &xi_point);
}; //end of 32 node element class


} //end namespace elements
} //end namespace ristra

#endif //ELEMENTS_H
