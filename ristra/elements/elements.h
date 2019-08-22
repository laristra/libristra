#ifndef ELEMENTS_H
#define ELEMENTS_H 

#include <iostream>

#include "ristra/elements/utilities.h"

namespace ristra{
namespace elements{

// Used by Gauss2/3D to set quadrature points
void LineGaussRuleInfo(
   real_t &x, real_t &w, 
   int &m,  int &p);

// Used by Lovatto 1D/2D to set Lobatto quadrature points
void LineLobattoRuleInfo(
   real_t &x, 
   real_t &w, 
   int &m, 
   int &p); // end of Lobatto line rule function      

// setting gauss quadrature points for 2D elements
void Gauss2D(
   vector< vector<real_t> > &these_g_pts,  // gauss points
   vector< vector<real_t> > &these_weights,// gauss weights
   vector<real_t> &tot_g_weight,           // 2D product of gauss weights
   int &quad_order);                       // quadrature order (m)

// setting gauss quadrature points for 2D elements
void Gauss3D(
   vector< vector<real_t> > &these_g_pts,   // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   vector<real_t> &tot_g_weight,            // 3D product of gauss weights
   int &quad_order);                        // quadrature order (n)

// setting gauss quadrature points for 4D elements
void Gauss4D(
   vector< vector<real_t> > &these_g_pts, // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   int &quad_order, // quadrature order (n)
   const int &dim);

// setting Gauss-Lobatto quadrature points for 2D elements
void Lobatto2D(
   vector< vector<real_t> > &these_L_pts, // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   int &quad_order); // quadrature order (n)

// setting Gauss-Lobatto quadrature points for 3D elements
void Lobatto3D(
   vector< vector<real_t> > &these_L_pts, // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   int &quad_order); 

// setting gauss quadrature points for 4D elements
void Lobatto4D(
   vector< vector<real_t> > &these_L_pts, // gauss points
   vector< vector<real_t> > &these_weights, // gauss weights
   int &quad_order, // quadrature order (n)
   const int &dim);

//defining the jacobian for 2D/3D elements
void jacobian(
   vector< vector<real_t> > &J_matrix, 
   real_t &det_J,
   const vector< vector<real_t> > &vertices, 
   const vector< vector<real_t> > &this_partial,
   const int &num_nodes,
   const int &dim);

//defining the jacobian for 4D elements
void jacobian4D(
   vector< vector<real_t> > &J_matrix, 
   real_t &det_J,
   const vector< vector<real_t> > &vertices, 
   const vector< vector<real_t> > &this_partial,
   const int &num_nodes,
   const int &dim);

//defining the inverse jacobian for 2D element    
void jacobian_inverse_2d(
   vector< vector<real_t> > &J_inverse, 
   const vector< vector<real_t> > &jacobian);

//defining the inverse jacobian for 2D element    
void jacobian_inverse_3d(
   vector<vector<real_t> > &J_inverse_matrix,
   const vector<vector<real_t> > &jacobian);

// defining  the inverse of the Jacobian for 4D elements
void jacobian_inverse_4d(
   vector<vector<real_t> > &J_inverse_matrix,
   const vector<vector<real_t> > &jacobian,
   const real_t &det_J);





class Element2D {
 
   public:


      // calculate a physical position in an element for a given xi,eta
      virtual void physical_position(vector <real_t> &x_2D_point,
                                     const vector <real_t> &xi_2D_point,
                                     const vector< vector<real_t> > &vertices) = 0;

      // calculate the value for the basis at each node for a given xi,eta
      virtual void basis(vector <real_t> &basis,
                         const vector <real_t> &xi_2D_point,
                         const vector< vector<real_t> > &vertices) = 0;

      // Partial derivative of shape functions with respect to Xi
      virtual void  partial_xi_shape_fcn(vector<real_t>  &partial_xi, 
                                         const vector <real_t> &xi_2D_point) = 0;

   
      // Partial derivative of shape functions with respect to Xi
      virtual void  partial_eta_shape_fcn(vector<real_t> &partial_eta, 
                                          const vector <real_t> &xi_2D_point) = 0;
}; // end of 2D element class

class Element3D {

   public:
   
      // calculate the volume of an element
      //virtual real_t volume(const vector< vector<real_t> > &vertices);
   
      // calculate a physical position in an element for a given xi,eta,mu
      virtual void physical_position(vector <real_t> &x_point,
                                     const vector <real_t> &xi_point,
                                     const vector< vector<real_t> > &vertices) = 0;

      // calculate the value for the basis at each node for a given xi,eta, mu
      virtual void basis(vector <real_t> &basis,
                         const vector <real_t> &xi_point,
                         const vector< vector<real_t> > &vertices) = 0;

      // Partial derivative of shape functions with respect to Xi at Xi_point
      virtual void partial_xi_shape_fcn(vector<real_t>  &partial_xi, 
                                        const vector <real_t> &xi_point) = 0;

      // Partial derivative of shape functions with respect to Eta
      virtual void partial_eta_shape_fcn(vector<real_t> &partial_eta, 
                                         const vector <real_t> &xi_point) = 0;

      // Partial derivative of shape functions with respect to Mu
      virtual void partial_mu_shape_fcn(vector<real_t> &partial_mu, 
                                        const vector <real_t> &xi_point) = 0;
}; // end of 3D parent class

class Element4D {

   public:

      // calculate a physical position in an element for a given xi,eta,mu
      virtual void physical_position(vector<real_t> &x_point,
                            const vector <real_t> &xi_point,
                            const vector< vector<real_t> > &vertices) = 0;

      // Partial derivative of shape functions with respect to Xi at Xi_point
      virtual void partial_xi_shape_fcn(vector<real_t>  &tess16_partial_xi, 
                                const vector <real_t> &xi_point) = 0;

      // Partial derivative of shape functions with respect to Eta
      virtual void partial_eta_shape_fcn(vector<real_t> &tess16_partial_eta, 
                                 const vector <real_t> &xi_point) = 0;

      // Partial derivative of shape functions with respect to Mu
      virtual void partial_mu_shape_fcn(vector<real_t> &tess16_partial_mu, 
                                const vector <real_t> &xi_point) = 0;

      // Partial derivative of shape functions with respect to Tau
      virtual void partial_tau_shape_fcn(vector<real_t> &tess16_partial_tau, 
                                 const vector <real_t> &xi_point) = 0;
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

     static real_t ref_vert[4][2]; // listed as {Xi, Eta}



   public:

      // calculate a physical position in an element for a given xi,eta
      void physical_position(vector <real_t> &x_point, 
                             const vector <real_t> &xi_2D_point, 
                             const vector< vector<real_t> > &vertices);
  
         real_t shape_fcn[4];
         real_t check_unity;

      // calculate the value for the basis at each node for a given xi,eta
      void basis(vector <real_t> &basis,
                 const vector <real_t> &xi_2D_point,
                 const vector< vector<real_t> > &vertices);

      // Partial derivative of shape functions with respect to Xi
      void  partial_xi_shape_fcn(vector<real_t>  &quad4_partial_xi, 
                                 const vector <real_t> &xi_2D_point);


      // Partial derivative of shape functions with respect to Eta
      void  partial_eta_shape_fcn(vector<real_t> &quad4_partial_eta, 
                                  const vector <real_t> &xi_2D_point);
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

      static real_t ref_vert[8][2];  // listed as {Xi, Eta}


      // calculate a physical position in an element for a given xi,eta,
      void physical_position(
               vector <real_t> &x_point, 
               const vector <real_t> &xi_2D_point, 
               const vector< vector<real_t> > &vertices);
  
         real_t shape_fcn[8];
         real_t check_unity;

      // calculate the value for the basis at each node for a given xi,eta
      void basis(vector <real_t> &basis,
                 const vector <real_t> &xi_2D_point,
                 const vector< vector<real_t> > &vertices); 

      // Partial derivative of shape functions with respect to Xi
      void partial_xi_shape_fcn(vector<real_t>  &quad8_partial_xi, 
                                 const vector <real_t> &xi_2D_point);

      // Partial derivative of shape functions with respect to Eta
      void partial_eta_shape_fcn(vector<real_t> &quad8_partial_eta, 
                                 const vector <real_t> &xi_2D_point);
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

      static real_t ref_vert[12][2];  // listed as {Xi, Eta}
        
      // calculate a physical position in an element for a given xi,eta,
      void physical_position(
               vector <real_t> &x_point, 
               const vector <real_t> &xi_point,
               const vector< vector<real_t> > &vertices);
  
         real_t shape_fcn[12];
         real_t check_unity;

      // calculate the value for the basis at each node for a given xi,eta
      void basis(vector <real_t> &basis,
                 const vector <real_t> &xi_2D_point,
                 const vector< vector<real_t> > &vertices);

      // Partial derivative of shape functions with respect to Xi
      void partial_xi_shape_fcn(vector<real_t>  &quad12_partial_xi, 
                                const vector <real_t> &xi_point);

      // Partial derivative of shape functions with respect to Eta
      void partial_eta_shape_fcn(vector<real_t> &quad12_partial_eta, 
                                 const vector <real_t> &xi_point);
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

      static real_t ref_vert[8][3];  // listed as {Xi, Eta, Mu}

   public:

      // get the physical location for a given xi_point
      void physical_position (vector <real_t> &x_point,
                              const vector <real_t> &xi_3D_point,
                              const vector< vector<real_t> > &vertices);
         int    dim;
         
         real_t shape_fcn[8];
         real_t check_unity;
      
      // calculate the value for the basis at each node for a given xi,eta, mu
      void basis(vector <real_t> &basis,
                 const vector <real_t> &xi_3D_point,
                 const vector< vector<real_t> > &vertices);

      // calculate the partials of the shape function 
      // with respect to Xi
      void partial_xi_shape_fcn(vector<real_t> &hex8_partial_xi, 
                                const vector <real_t> &xi_3D_point);

      // with respect to Eta
      void partial_eta_shape_fcn(vector<real_t> &hex8_partial_eta, 
                                 const vector <real_t> &xi_3D_point);

      // with repsect to Mu
      void partial_mu_shape_fcn(vector<real_t> &hex8_partial_mu, 
                                const vector <real_t> &xi_3D_point);
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

    static real_t ref_vert[20][3]; // listed as {Xi, Eta, Mu}

      // get the physical location for a given xi_3D_point
      void physical_position (vector <real_t> &x_point,
                              const vector <real_t> &xi_3D_point,
                              const vector< vector<real_t> > &vertices);
      
         int    this_vert;
         int    dim;
      
         real_t shape_fcn[20];
         real_t check_unity;
     
      // calculate the value for the basis at each node for a given xi,eta, mu
      void basis(vector <real_t> &basis,
                 const vector <real_t> &xi_3D_point,
                 const vector< vector<real_t> > &vertices);

      // Calculate the partials of the shape functions
      // with respect to Xi
      void  partial_xi_shape_fcn(vector<real_t> &hex20_partial_xi, 
                                 const vector <real_t> &xi_3D_point);

      // with respect to Eta
      void partial_eta_shape_fcn(vector<real_t> &hex20_partial_eta, 
                                 const vector <real_t> &xi_3D_point);
      // with repsect to mu
      void partial_mu_shape_fcn(vector<real_t> &hex20_partial_mu, 
                                const vector <real_t> &xi_3D_point);
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

      static  real_t ref_vert[32][3]; // listed as {Xi, Eta, Mu}
 
      // get the physical location for a given xi_3D_point
      void physical_position (vector <real_t> &x_point,
                             const vector <real_t> &xi_3D_point,
                             const vector< vector<real_t> > &vertices);

         int    dim;
      
         real_t shape_fcn[32];
         real_t check_unity;

      // calculate the value for the basis at each node for a given xi,eta, mu
      void basis(vector <real_t> &basis,
                 const vector <real_t> &xi_3D_point,
                 const vector< vector<real_t> > &vertices);
      
      // Calculate the partials of the shape functions
      // with respect to Xi
      void  partial_xi_shape_fcn(vector<real_t> &hex32_partial_xi, 
                                 const vector <real_t> &xi_3D_point);

      // with respect to Eta
      void partial_eta_shape_fcn(vector<real_t> &hex32_partial_eta, 
                                 const vector <real_t> &xi_3D_point);
      // with repsect to mu
      void partial_mu_shape_fcn(vector<real_t> &hex32_partial_mu, 
                                const vector <real_t> &xi_3D_point);
}; //end of 32 node element class



/*

 ==========================
  Arbitrary Order Elements
 ==========================
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

class QuadN{
   public:

      // creates nodal positions with Chebyshev spacing
      void chebyshev_nodes_1D(
         vector<real_t> &cheb_nodes_1D,  // Chebyshev nodes
         const int &orderN);              // Interpolation order

      // calculates the basis values and derivatives in 1D
      // used in teh basis_partials functiosn to build the 3D element
      void lagrange_1D(
         vector <real_t> &interp,            // interpolant
         vector <real_t> &Dinterp,           // derivative of function
         const real_t &x_point,              // point of interest in element
         const vector <real_t> &xi_point,    // nodal positions in 1D, normally chebyshev
         const int &orderN);                 // order of element

      void corners (
         vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements 
         vector< vector<real_t> > &lag_corner,  // corner nodes of HexN element
         const int &orderN);                    // Element order)
      
      void physical_position (
         vector <real_t> &x_point,                    // location in real space
         const vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements 
         const vector <real_t> &lag_basis_2d,         // 2D basis values 
         const int &orderN);                          // order of the element
      
      void basis_partials (
         vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements (to be filled in)
         vector <real_t> &nodes_1d,             // Nodal spacing in 1D, any spacing is accepted
         vector <real_t> &val_1d,               // Interpolant Value in 1D
         vector <real_t> &DVal_1d,              // Derivateive of basis in 1D
         vector< vector<real_t> >  &val_2d,     // for holding the interpolant in each direction
         vector< vector<real_t> >  &DVal_2d,    // for holding the derivatives in each direction
         vector <real_t> &lag_basis_2d,         // 3D basis values 
         vector< vector<real_t> > &lag_partial, // Partial of basis 
         const vector <real_t> &xi_point,       // point of interest
         const int &orderN);                    // Element order
};


class HexN{
   public:

      // creates nodal positions with Chebyshev spacing
      void chebyshev_nodes_1D(
         vector<real_t> &cheb_nodes_1D,  // Chebyshev nodes
         const int &orderN);              // Interpolation order

      // calculates the basis values and derivatives in 1D
      // used in teh basis_partials functiosn to build the 3D element
      void lagrange_1D(
         vector <real_t> &interp,            // interpolant
         vector <real_t> &Dinterp,           // derivative of function
         const real_t &x_point,              // point of interest in element
         const vector <real_t> &xi_point,    // nodal positions in 1D, normally chebyshev
         const int &orderN);                 // order of element

      void corners (
         vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements 
         vector< vector<real_t> > &lag_corner,  // corner nodes of HexN element
         const int &orderN);                    // Element order)
      
      void physical_position (
         vector <real_t> &x_point,                    // location in real space
         const vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements 
         const vector <real_t> &lag_basis_3d,         // 3D basis values 
         const int &orderN);                          // order of the element
      
      void basis_partials (
         vector< vector<real_t> > &lag_nodes,   // Nodes of Lagrange elements (to be filled in)
         vector <real_t> &nodes_1d,             // Nodal spacing in 1D, any spacing is accepted
         vector <real_t> &val_1d,               // Interpolant Value in 1D
         vector <real_t> &DVal_1d,              // Derivateive of basis in 1D
         vector< vector<real_t> >  &val_3d,     // for holding the interpolant in each direction
         vector< vector<real_t> >  &DVal_3d,    // for holding the derivatives in each direction
         vector <real_t> &lag_basis_3d,         // 3D basis values 
         vector< vector<real_t> > &lag_partial, // Partial of basis 
         const vector <real_t> &xi_point,       // point of interest
         const int &orderN);                    // Element order
};




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

class Tess16: public Element4D {
   protected:
      int  num_nodes;

      real_t ref_vert[16][4];  // listed as {Xi, Eta, Mu, Tau}



   public:

      // calculate a physical position in an element for a given xi,eta,mu
      void physical_position(vector <real_t> &x_point,
                            const vector <real_t> &xi_4D_point,
                            const vector< vector<real_t> > &vertices);

      // Partial derivative of shape functions with respect to Xi at Xi_point
      void partial_xi_shape_fcn(vector<real_t>  &tess16_partial_xi, 
                                const vector <real_t> &xi_4D_point);

      // Partial derivative of shape functions with respect to Eta
      void partial_eta_shape_fcn(vector<real_t> &tess16_partial_eta, 
                                 const vector <real_t> &xi_4D_point);

      // Partial derivative of shape functions with respect to Mu
      void partial_mu_shape_fcn(vector<real_t> &tess16_partial_mu, 
                                const vector <real_t> &xi_4D_point);

      // Partial derivative of shape functions with respect to Tau
      void partial_tau_shape_fcn(vector<real_t> &tess16_partial_tau, 
                                 const vector <real_t> &xi_4D_point);                                          
}; // End of Tess16 Element Class







} //end namespace elements
} //end namespace ristra

#endif //ELEMENTS_H
