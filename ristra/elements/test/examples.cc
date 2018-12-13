//   ____               _____ _       _  _                              
//  / ___|  _     _    |  ___(_)_ __ (_)| |_   ___  
// | |    _| |_ _| |_  | |_  | | '_ \| || __| / _ \ 
// | |___|_   _|_   _| |  _| | | | | | || |  |  __/ 
//  \____| |_|   |_|   |_|   |_|_| |_|_| \_\  \___|
//  _____ _                           _     _     _ _                          
// | ____| | ___ _ __ ___   ___ _ __ | |_  | |   (_| |__  _ __ __ _ _ __ _   _ 
// |  _| | |/ _ | '_ ` _ \ / _ | '_ \| __| | |   | | '_ \| '__/ _` | '__| | | |
// | |___| |  __| | | | | |  __| | | | |_  | |___| | |_) | | | (_| | |  | |_| |
// |_____|_|\___|_| |_| |_|\___|_| |_|\__| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                                       |___/

#include <stdio.h>
#include <iostream>  // std::cout etc.
#include <cmath>

#include <cinchtest.h>

#include "ristra/elements/elements.h"
#include "ristra/elements/utilities.h"

namespace elements = ristra::elements;
using ristra::elements::vector;
using real_t = double;


/*
 _____ _                           _   
| ____| | ___ _ __ ___   ___ _ __ | |_ 
|  _| | |/ _ | '_ ` _ \ / _ | '_ \| __|
| |___| |  __| | | | | |  __| | | | |_ 
|_____|_|\___|_| |_| |_|\___|_| |_|\__|
 ______        _
|_   __|______| |_                      
  | | / _ / __| __|                     
  | |{  __\__ | |_                      
  |_| \___|___/\__|    
*/
// Main function for the program
TEST(elements, all) {

   // variables for position
   real_t X = 0.0;
   real_t Y = 0.0;
   real_t Z = 0.0;

   //Test function order controls
   int n_i = 2;
   int n_j = 2;
   int n_k = 2;
   
   // (DISABLED) user input for arbitrary point in element and funciton order

   // std::cout << "Enter coordinates to check element"<< std::endl;
   // std::cout << "Enter X (-1 < X <  1):" ;
   // std::cin >> X;

   // std::cout << "Enter Y (-1 < Y <  1):" ;
   // std::cin >> Y;

   // std::cout << "Enter Z (-1 < Z <  1):" ;
   // std::cin >> Z;


   // std::cout << "Enter function order n_i:" ;
   // std::cin >> n_i;

   // std::cout << "Enter function order n_j:" ;
   // std::cin >> n_j;
   // 
   // std::cout << "Enter function order n_k:" ;
   // std::cin >> n_k;

   
   int order = n_i + n_j + n_k;    // Function order for integration testing

   vector <real_t> xi_2D_point{X,Y};     // 2D arbitraty reference point for testing   
   vector <real_t> xi_point{X,Y,Z};      // 3D arbitrary reference point for testing

   // (DISABLED) user input for quadrature order
   int quad_order = 2;
   // std::cout << "Enter Quadrature order. Current options = (1,2,3,4,5,6,7,8):" ;
   // std::cin >> quad_order;

   //number of qiadrature points in 3D
   int tot_q_pts_3d = quad_order * quad_order * quad_order; 

   //number of qiadrature points in 2D
   int tot_q_pts_2d = quad_order * quad_order; 


// vector definiteion 
   // create element node vectors
   vector<vector<real_t> > quad4_x_verts (4 , vector<real_t>(2));
   vector<vector<real_t> > quad8_x_verts (8 , vector<real_t>(2));
   vector<vector<real_t> > quad12_x_verts(12, vector<real_t>(2));

   vector<vector<real_t> > hex8_x_verts  (8 , vector<real_t>(3));
   vector<vector<real_t> > hex20_x_verts (20, vector<real_t>(3));
   vector<vector<real_t> > hex32_x_verts (32, vector<real_t>(3));

   // create vector for storing basis values
   vector <real_t> quad4_basis (4);
   vector <real_t> quad8_basis (8);
   vector <real_t> quad12_basis (12);

   vector <real_t> hex8_basis  (8);
   vector <real_t> hex20_basis (20);
   vector <real_t> hex32_basis (32);

   // create vectors of gauss points
   vector< vector<real_t> > quad4_g_pts ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad8_g_pts ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad12_g_pts( tot_q_pts_2d, vector<real_t>(2));

   vector< vector<real_t> > hex8_g_pts  ( tot_q_pts_3d, vector<real_t>(3));
   vector< vector<real_t> > hex20_g_pts ( tot_q_pts_3d, vector<real_t>(3));
   vector< vector<real_t> > hex32_g_pts ( tot_q_pts_3d, vector<real_t>(3));

   //create vectors of gauss points in real space
   vector< vector<real_t> > quad4_g_pts_real ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad8_g_pts_real ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad12_g_pts_real( tot_q_pts_2d, vector<real_t>(2));

   vector< vector<real_t> > hex8_g_pts_real  ( tot_q_pts_3d, vector<real_t>(3));
   vector< vector<real_t> > hex20_g_pts_real ( tot_q_pts_3d, vector<real_t>(3));
   vector< vector<real_t> > hex32_g_pts_real ( tot_q_pts_3d, vector<real_t>(3));

   
   // create vectors of gauss weights
   vector< vector<real_t> > quad4_g_weights ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad8_g_weights ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad12_g_weights( tot_q_pts_2d, vector<real_t>(2));

   vector< vector<real_t> > hex8_g_weights  ( tot_q_pts_3d, vector<real_t>(3)); 
   vector< vector<real_t> > hex20_g_weights ( tot_q_pts_3d, vector<real_t>(3)); 
   vector< vector<real_t> > hex32_g_weights ( tot_q_pts_3d, vector<real_t>(3)); 
   
   // Create values for combination of gauss weights
   vector<real_t> quad4_weight (tot_q_pts_2d);
   vector<real_t> quad8_weight (tot_q_pts_2d);
   vector<real_t> quad12_weight(tot_q_pts_2d);

   vector<real_t> hex8_weight (tot_q_pts_3d);
   vector<real_t> hex20_weight(tot_q_pts_3d);
   vector<real_t> hex32_weight(tot_q_pts_3d);

   // create vectors of Gauss-Lobatto points
   vector< vector<real_t> > quad4_l_pts ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad8_l_pts ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad12_l_pts( tot_q_pts_2d, vector<real_t>(2));

   vector< vector<real_t> > hex8_l_pts  ( tot_q_pts_3d, vector<real_t>(3));
   vector< vector<real_t> > hex20_l_pts ( tot_q_pts_3d, vector<real_t>(3));
   vector< vector<real_t> > hex32_l_pts ( tot_q_pts_3d, vector<real_t>(3));


   // create vectors of Gauss-Lobatto weights
   vector< vector<real_t> > quad4_l_weights ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad8_l_weights ( tot_q_pts_2d, vector<real_t>(2));
   vector< vector<real_t> > quad12_l_weights( tot_q_pts_2d, vector<real_t>(2));

   vector< vector<real_t> > hex8_l_weights  ( tot_q_pts_3d, vector<real_t>(3)); 
   vector< vector<real_t> > hex20_l_weights ( tot_q_pts_3d, vector<real_t>(3)); 
   vector< vector<real_t> > hex32_l_weights ( tot_q_pts_3d, vector<real_t>(3)); 


   // create partial derivative vectors for basis (shape) functions
   //xi
   vector <real_t> quad4_partial_xi(4);
   vector< vector<real_t> > quad4_q_partial_xi( tot_q_pts_2d, vector<real_t>(4));

   vector <real_t> quad8_partial_xi(8);
   vector< vector<real_t> > quad8_q_partial_xi( tot_q_pts_2d, vector<real_t>(8));

   vector <real_t> quad12_partial_xi(12);
   vector< vector<real_t> > quad12_q_partial_xi( tot_q_pts_2d, vector<real_t>(12));


   vector <real_t> hex8_partial_xi(8);
   vector< vector<real_t> > hex8_q_partial_xi(tot_q_pts_3d, vector<real_t>(8));

   vector <real_t> hex20_partial_xi(20);
   vector< vector<real_t> > hex20_q_partial_xi(tot_q_pts_3d, vector<real_t>(20));

   vector <real_t> hex32_partial_xi(32);
   vector< vector<real_t> > hex32_q_partial_xi(tot_q_pts_3d, vector<real_t>(32));


   //eta
   vector <real_t> quad4_partial_eta(4);
   vector< vector<real_t> > quad4_q_partial_eta( tot_q_pts_2d, vector<real_t>(4));

   vector <real_t> quad8_partial_eta(8);
   vector< vector<real_t> > quad8_q_partial_eta( tot_q_pts_2d, vector<real_t>(8));

   vector <real_t> quad12_partial_eta(12);
   vector< vector<real_t> > quad12_q_partial_eta( tot_q_pts_2d, vector<real_t>(12));


   vector <real_t> hex8_partial_eta(8);
   vector< vector<real_t> >  hex8_q_partial_eta(tot_q_pts_3d, vector<real_t>(8)); 

   vector <real_t> hex20_partial_eta(20);
   vector< vector<real_t> > hex20_q_partial_eta(tot_q_pts_3d, vector<real_t>(20));

   vector <real_t> hex32_partial_eta(32);
   vector< vector<real_t> > hex32_q_partial_eta(tot_q_pts_3d, vector<real_t>(32));

   //mu
   vector <real_t> hex8_partial_mu(8);
   vector< vector<real_t> > hex8_q_partial_mu(tot_q_pts_3d, vector<real_t>(8));

   vector <real_t> hex20_partial_mu(20);
   vector< vector<real_t> > hex20_q_partial_mu(tot_q_pts_3d, vector<real_t>(20));

   vector <real_t> hex32_partial_mu(32);
   vector< vector<real_t> > hex32_q_partial_mu(tot_q_pts_3d, vector<real_t>(32));



   //overall partial derivative matrix (to combine Xi/Eta/Mu)
   // for Hex 8
   vector<vector<real_t> > hex8_partial(8, vector<real_t>(3));
   vector<vector<vector<real_t>> > hex8_q_partial(tot_q_pts_3d, vector<vector<real_t>>(8, vector<real_t>(3)));
   // for Hex 20
   vector<vector<real_t> > hex20_partial(20, vector<real_t>(3));
   vector<vector<vector<real_t>> > hex20_q_partial(tot_q_pts_3d, vector<vector<real_t>>(20, vector<real_t>(3)));
   // for Hex 32
   vector<vector<real_t> > hex32_partial(32, vector<real_t>(3));
   vector<vector<vector<real_t>> > hex32_q_partial(tot_q_pts_3d, vector<vector<real_t>>(32, vector<real_t>(3)));
   // for Quad 4
   vector<vector<real_t> > quad4_partial(4, vector<real_t>(2));
   vector<vector<vector<real_t>> > quad4_q_partial(tot_q_pts_2d, vector<vector<real_t>>(4, vector<real_t>(2)));
   // for Quad 8
   vector<vector<real_t> > quad8_partial(8, vector<real_t>(2));
   vector<vector<vector<real_t>> > quad8_q_partial(tot_q_pts_2d, vector<vector<real_t>>(8, vector<real_t>(2)));
   // for Quad 12
   vector<vector<real_t> > quad12_partial(12, vector<real_t>(2));
   vector<vector<vector<real_t>> > quad12_q_partial(tot_q_pts_2d, vector<vector<real_t>>(12, vector<real_t>(2)));


   // create jacobian matrices
   vector<vector<real_t> > quad4_jacobian (3, vector<real_t>(3));
   vector<vector<real_t> > quad8_jacobian (3, vector<real_t>(3));
   vector<vector<real_t> > quad12_jacobian(3, vector<real_t>(3));

   vector<vector<real_t> > hex8_jacobian  (3, vector<real_t>(3));
   vector<vector<real_t> > hex20_jacobian (3, vector<real_t>(3));
   vector<vector<real_t> > hex32_jacobian (3, vector<real_t>(3));

   // create determinant 
   real_t hex8_det_j;
   real_t hex20_det_j;
   real_t hex32_det_j;
   real_t quad4_det_j;
   real_t quad8_det_j;
   real_t quad12_det_j;
   vector <real_t> hex8_q_det_j  (tot_q_pts_3d);
   vector <real_t> hex20_q_det_j (tot_q_pts_3d);
   vector <real_t> hex32_q_det_j (tot_q_pts_3d);
   vector <real_t> quad4_q_det_j (tot_q_pts_2d);
   vector <real_t> quad8_q_det_j (tot_q_pts_2d);
   vector <real_t> quad12_q_det_j(tot_q_pts_2d);


   // matrix of jacobian matrices per quad point (data matrix locations = (quad_point, i, j)

   vector<vector<vector<real_t>> > quad4_q_jacobian (tot_q_pts_2d, vector<vector<real_t>>(3, vector<real_t>(3)));
   vector<vector<vector<real_t>> > quad8_q_jacobian (tot_q_pts_2d, vector<vector<real_t>>(3, vector<real_t>(3)));
   vector<vector<vector<real_t>> > quad12_q_jacobian(tot_q_pts_2d, vector<vector<real_t>>(3, vector<real_t>(3)));

   vector<vector<vector<real_t>> > hex8_q_jacobian  (tot_q_pts_3d, vector<vector<real_t>>(3, vector<real_t>(3)));
   vector<vector<vector<real_t>> > hex20_q_jacobian (tot_q_pts_3d, vector<vector<real_t>>(3, vector<real_t>(3)));
   vector<vector<vector<real_t>> > hex32_q_jacobian (tot_q_pts_3d, vector<vector<real_t>>(3, vector<real_t>(3)));
   


   // create inverse jacobian matrices
   vector<vector<real_t> > quad4_inverse_jacobian (2, vector<real_t>(2));
   vector<vector<real_t> > quad8_inverse_jacobian (2, vector<real_t>(2));
   vector<vector<real_t> > quad12_inverse_jacobian(2, vector<real_t>(2));

   vector<vector<real_t> > hex8_inverse_jacobian  (3, vector<real_t>(3));
   vector<vector<real_t> > hex20_inverse_jacobian (3, vector<real_t>(3));
   vector<vector<real_t> > hex32_inverse_jacobian (3, vector<real_t>(3));

   // matrix of inverse jacobian matrices per quad point (quad_point, i, j)
   vector<vector<vector<real_t>> > quad4_q_inverse_jacobian (tot_q_pts_2d, vector<vector<real_t>>(2, vector<real_t>(2)));
   vector<vector<vector<real_t>> > quad8_q_inverse_jacobian (tot_q_pts_2d, vector<vector<real_t>>(2, vector<real_t>(2))); 
   vector<vector<vector<real_t>> > quad12_q_inverse_jacobian(tot_q_pts_2d, vector<vector<real_t>>(2, vector<real_t>(2)));

   vector<vector<vector<real_t>> > hex8_q_inverse_jacobian  (tot_q_pts_3d, vector<vector<real_t>>(3, vector<real_t>(3)));
   vector<vector<vector<real_t>> > hex20_q_inverse_jacobian (tot_q_pts_3d, vector<vector<real_t>>(3, vector<real_t>(3)));
   vector<vector<vector<real_t>> > hex32_q_inverse_jacobian (tot_q_pts_3d, vector<vector<real_t>>(3, vector<real_t>(3)));
// end vector definition 


// Position vector initialization
   // create notational coordinates for Quad4 element
   quad4_x_verts[0] = {-1.0, -1.0};
   quad4_x_verts[1] = { 1.0, -1.0};
   quad4_x_verts[2] = { 1.0,  1.0};
   quad4_x_verts[3] = {-1.0,  1.0};

   //create notational coordinates for the Quad8 element
   // corners
   quad8_x_verts[0] = {-1.0, -1.0};
   quad8_x_verts[1] = { 1.0, -1.0};
   quad8_x_verts[2] = { 1.0,  1.0};
   quad8_x_verts[3] = {-1.0,  1.0};
   // middle edges
   quad8_x_verts[4] = { 0.0, -1.0};
   quad8_x_verts[5] = { 1.0,  0.0};
   quad8_x_verts[6] = { 0.0,  1.0};
   quad8_x_verts[7] = {-1.0,  0.0};

   //create notational coordinates for the Quad 12 element
   // corners
   quad12_x_verts[0] = {-1.0, -1.0};
   quad12_x_verts[1] = { 1.0, -1.0};
   quad12_x_verts[2] = { 1.0,  1.0};
   quad12_x_verts[3] = {-1.0,  1.0};
   // Eta +- 1./3.
   quad12_x_verts[4] = {-1./3., -1.0};
   quad12_x_verts[5] = { 1./3., -1.0};
   quad12_x_verts[6] = { 1./3.,  1.0};
   quad12_x_verts[7] = {-1./3.,  1.0};
   // Xi +- 1./3.
   quad12_x_verts[8]  = {-1.0, -1./3.};
   quad12_x_verts[9]  = { 1.0, -1./3.};
   quad12_x_verts[10] = { 1.0,  1./3.};
   quad12_x_verts[11] = {-1.0,  1./3.};


   // create notional coordinates for a Hex8 element
   hex8_x_verts[0] = {-1.0, -1.0, -1.0};
   hex8_x_verts[1] = {+1.0, -1.0, -1.0};
   hex8_x_verts[2] = {+1.0, -1.0, +1.0};
   hex8_x_verts[3] = {-1.0, -1.0, +1.0};
   hex8_x_verts[4] = {-1.0, +1.0, -1.0};
   hex8_x_verts[5] = {+1.0, +1.0, -1.0};
   hex8_x_verts[6] = {+1.0, +1.0, +1.0};
   hex8_x_verts[7] = {-1.0, +1.0, +1.0};
   
   
   // create notional coordinates for a Hex20 element
   // the corners
   hex20_x_verts[0] = {-1.0, -1.0, -1.0};
   hex20_x_verts[1] = {+1.0, -1.0, -1.0};
   hex20_x_verts[2] = {+1.0, -1.0, +1.0};
   hex20_x_verts[3] = {-1.0, -1.0, +1.0};
   hex20_x_verts[4] = {-1.0, +1.0, -1.0};
   hex20_x_verts[5] = {+1.0, +1.0, -1.0};
   hex20_x_verts[6] = {+1.0, +1.0, +1.0};
   hex20_x_verts[7] = {-1.0, +1.0, +1.0};
   // bottom edges
   hex20_x_verts[8]  = { 0.0, -1.0, -1.0};
   hex20_x_verts[9]  = {+1.0, -1.0,  0.0};
   hex20_x_verts[10] = { 0.0, -1.0, +1.0};
   hex20_x_verts[11] = {-1.0, -1.0,  0.0};
   // top edges
   hex20_x_verts[12] = { 0.0, +1.0, -1.0};
   hex20_x_verts[13] = {+1.0, +1.0,  0.0};
   hex20_x_verts[14] = { 0.0, +1.0, +1.0};
   hex20_x_verts[15] = {-1.0, +1.0,  0.0};
   // middle edges
   hex20_x_verts[16] = {-1.0, 0.0, -1.0};
   hex20_x_verts[17] = {+1.0, 0.0, -1.0};
   hex20_x_verts[18] = {+1.0, 0.0, +1.0};
   hex20_x_verts[19] = {-1.0, 0.0, +1.0};


   // create notional coordinates for a Hex32 element
   // the corners
   hex32_x_verts[0] = {-1.0, -1.0, -1.0};
   hex32_x_verts[1] = {+1.0, -1.0, -1.0};
   hex32_x_verts[2] = {+1.0, -1.0, +1.0};
   hex32_x_verts[3] = {-1.0, -1.0, +1.0};
   hex32_x_verts[4] = {-1.0, +1.0, -1.0};
   hex32_x_verts[5] = {+1.0, +1.0, -1.0};
   hex32_x_verts[6] = {+1.0, +1.0, +1.0};
   hex32_x_verts[7] = {-1.0, +1.0, +1.0};
   // Xi/Eta = +- 1
   hex32_x_verts[8]  = {-1.0, -1.0, -1./3.};
   hex32_x_verts[9]  = { 1.0, -1.0, -1./3.};
   hex32_x_verts[10] = { 1.0, -1.0,  1./3.};
   hex32_x_verts[11] = {-1.0, -1.0,  1./3.};
   hex32_x_verts[12] = {-1.0,  1.0, -1./3.};
   hex32_x_verts[13] = { 1.0,  1.0, -1./3.};
   hex32_x_verts[14] = { 1.0,  1.0,  1./3.};
   hex32_x_verts[15] = {-1.0,  1.0,  1./3.};
   // Eta/Mu = +- 1
   hex32_x_verts[16] = {-1./3., -1.0, -1.0};
   hex32_x_verts[17] = { 1./3., -1.0, -1.0};
   hex32_x_verts[18] = { 1./3., -1.0,  1.0};
   hex32_x_verts[19] = {-1./3., -1.0,  1.0};
   hex32_x_verts[20] = {-1./3.,  1.0, -1.0};
   hex32_x_verts[21] = { 1./3.,  1.0, -1.0};
   hex32_x_verts[22] = { 1./3.,  1.0,  1.0};
   hex32_x_verts[23] = {-1./3.,  1.0,  1.0};
   // Xi/Mu = +- 1
   hex32_x_verts[24] = {-1.0, -1./3., -1.0};
   hex32_x_verts[25] = { 1.0, -1./3., -1.0};
   hex32_x_verts[26] = { 1.0, -1./3.,  1.0};
   hex32_x_verts[27] = {-1.0, -1./3.,  1.0};
   hex32_x_verts[28] = {-1.0,  1./3., -1.0};
   hex32_x_verts[29] = { 1.0,  1./3., -1.0};
   hex32_x_verts[30] = { 1.0,  1./3.,  1.0};
   hex32_x_verts[31] = {-1.0,  1./3.,  1.0};   

// End position vector initialization  

   // a point in the element for testing purposes
   
   vector <real_t> x_2D_point(2);
   vector <real_t> x_point(3);
   
   
// create element types
   elements::Hex8          hex8_element;
   elements::Hex20         hex20_element;
   elements::Hex32         hex32_element;
   elements::Quad_4_2D     quad4_element;
   elements::Quad_8_2D     quad8_element;
   elements::Quad_12_2D    quad12_element;
   

   //Elements to add
   // Tet4
   // Tet10
   // Polytope
   

   // store the address of the element types
   // 3D elements
   elements::Element3D *this_hex8         = &hex8_element;
   elements::Element3D *this_hex20        = &hex20_element;
   elements::Element3D *this_hex32        = &hex32_element;

   // 2D elements
   elements::Element2D *this_quad4        = &quad4_element;
   elements::Element2D *this_quad8        = &quad8_element;
   elements::Element2D *this_quad12       = &quad12_element;

// Linearly shifting/scaling position vectors
   bool shift = false;
   if(shift){

      //Quad4
      for(int this_vert=0; this_vert < 4; this_vert++){
         for(int this_dim = 0; this_dim < 2 ; this_dim++){
            quad4_x_verts[this_vert][this_dim] = 
            (quad4_x_verts[this_vert][this_dim] + 1.0)/2.0;
         }
      }

      //Quad8
      for(int this_vert=0; this_vert < 8; this_vert++){
         for(int this_dim = 0; this_dim < 2 ; this_dim++){
            quad8_x_verts[this_vert][this_dim] = 
            (quad8_x_verts[this_vert][this_dim] + 1.0)/2.0;
         }
      }
      
      //Quad12
      for(int this_vert=0; this_vert < 12; this_vert++){
         for(int this_dim = 0; this_dim < 2 ; this_dim++){
            quad12_x_verts[this_vert][this_dim] = 
            (quad12_x_verts[this_vert][this_dim] + 1.0)/2.0;
         }
      }

      //Hex8
      for(int this_vert=0; this_vert < 8; this_vert++){
         for(int this_dim = 0; this_dim < 3 ; this_dim++){
            hex8_x_verts[this_vert][this_dim] = 
            (hex8_x_verts[this_vert][this_dim] + 1.0)/2.0;
         }
      }

      //Hex20
      for(int this_vert=0; this_vert < 20; this_vert++){
         for(int this_dim = 0; this_dim < 3 ; this_dim++){
            hex20_x_verts[this_vert][this_dim] = 
            (hex20_x_verts[this_vert][this_dim] + 1.0)/2.0;
         }
      }

      //Hex32
      for(int this_vert=0; this_vert < 32; this_vert++){
         for(int this_dim = 0; this_dim < 3 ; this_dim++){
            hex32_x_verts[this_vert][this_dim] = 
            (hex32_x_verts[this_vert][this_dim] + 1.0)/2.0;
         }
      }


   }//end if shift
// End shifting/scaling position vectors
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

int dim_2d = 2; // number of dimensions

  /////////////////////////////
  //     Quad 4 element      //
////////////////////////////// 

   int quad4_pts = 4; // number of nodes

   //call the quad4 functions

   //call the gauss quadrature functions to set points/weights
   elements::Gauss2D(quad4_g_pts, quad4_g_weights, quad4_weight, quad_order);

   this_quad4 -> physical_position(x_2D_point, xi_2D_point, quad4_x_verts);

   //storing the values for the basis functions
   this_quad4 -> basis(quad4_basis, xi_2D_point, quad4_x_verts);

   // defining the partials
   this_quad4 -> partial_xi_shape_fcn(quad4_partial_xi, xi_2D_point);
   this_quad4 -> partial_eta_shape_fcn(quad4_partial_eta, xi_2D_point);             

   // defining the partials per gauss point
   for (int i = 0; i < tot_q_pts_2d; i++){
      this_quad4 -> partial_xi_shape_fcn(quad4_q_partial_xi[i], quad4_g_pts[i]);
   }
   for (int i = 0; i < tot_q_pts_2d; i++){
      this_quad4 -> partial_eta_shape_fcn(quad4_q_partial_eta[i], quad4_g_pts[i]);
   }

   //creating matrix of partials
   for (int i = 0; i < quad4_pts; i++){ // looping over the nodes
      quad4_partial[i][0] = quad4_partial_xi[i];
      quad4_partial[i][1] = quad4_partial_eta[i];
   }

   // creating matrix of Quad 4 quad point partials
   for (int i = 0; i < tot_q_pts_2d; i++){ //looping over the quad points
      for (int j = 0; j < quad4_pts; j++){ //looping over the nodes
         quad4_q_partial[i][j][0] = quad4_q_partial_xi[i][j];
         quad4_q_partial[i][j][1] = quad4_q_partial_eta[i][j];
      }
   }

   // calling the jacobian/inverse
   elements::jacobian(quad4_jacobian, quad4_det_j, quad4_x_verts, 
      quad4_partial, quad4_pts, dim_2d);
   elements::jacobian_inverse_2d(quad4_inverse_jacobian, quad4_jacobian);

   // calling the jacobian/inverse for quad points
   for (int i = 0; i < tot_q_pts_2d; i++){ //looping over the quad points
      elements::jacobian(quad4_q_jacobian[i], quad4_q_det_j[i], 
         quad4_x_verts, quad4_q_partial[i], quad4_pts, dim_2d);
   }

   for (int i = 0; i < tot_q_pts_2d; i++){ // looping over the quadrature points
      elements::jacobian_inverse_2d(quad4_q_inverse_jacobian[i], quad4_q_jacobian[i]);
   }

// end of quad 4

  /////////////////////////////
  //     Quad 8 element      //
/////////////////////////////// 
   
   int quad8_pts = 8;
   //call the quad8 functions

   //call the gauss quadrature functions to set points/g_weights
   elements::Gauss2D( quad8_g_pts, quad8_g_weights, quad8_weight, quad_order);
   this_quad8 -> physical_position(x_2D_point, xi_2D_point, quad8_x_verts);

   //storing the values for the basis functions
   this_quad8 -> basis(quad8_basis, xi_2D_point, quad8_x_verts);

   // Calling the partial functions
   this_quad8 -> partial_xi_shape_fcn(quad8_partial_xi, xi_2D_point);
   this_quad8 -> partial_eta_shape_fcn(quad8_partial_eta, xi_2D_point);

   //creating matrix of partials
   for (int i = 0; i < quad8_pts; i++){
      quad8_partial[i][0] = quad8_partial_xi[i];
      quad8_partial[i][1] = quad8_partial_eta[i];
   }// end for

   // defining the partials per gauss point
   for (int i = 0; i < tot_q_pts_2d; i++){
      this_quad8 -> partial_xi_shape_fcn(quad8_q_partial_xi[i], quad8_g_pts[i]);
   }

   for (int i = 0; i < tot_q_pts_2d; i++){
      this_quad8 -> partial_eta_shape_fcn(quad8_q_partial_eta[i], quad8_g_pts[i]);
   }

   // creating matrix of Quad 8 quad point partials
   for (int i = 0; i < tot_q_pts_2d; i++){
      for (int j = 0; j < quad8_pts; j++){
         quad8_q_partial[i][j][0] = quad8_q_partial_xi[i][j];
         quad8_q_partial[i][j][1] = quad8_q_partial_eta[i][j];
      } // end for j
   }// end for i

   // calling the jacobian/inverse
   elements::jacobian(quad8_jacobian, quad8_det_j, quad8_x_verts, 
      quad8_partial, quad8_pts, dim_2d);
   elements::jacobian_inverse_2d(quad8_inverse_jacobian, quad8_jacobian);

   // calling the jacobian/inverse for quad points
   for (int i = 0; i < tot_q_pts_2d; i++){
      elements::jacobian(quad8_q_jacobian[i], quad8_q_det_j[i], 
         quad8_x_verts, quad8_q_partial[i], quad8_pts, dim_2d);
   }
   for (int i = 0; i < tot_q_pts_2d; i++){ // looping over the quadrature points
      elements::jacobian_inverse_2d(quad8_q_inverse_jacobian[i], quad8_q_jacobian[i]);
   }
// end of quad 8

  /////////////////////////////
  //     Quad 12 element      //
/////////////////////////////// 
   
   int quad12_pts = 12;
   //call the quad12 functions

   //call the gauss quadrature functions to set points/g_weights
   elements::Gauss2D( quad12_g_pts, quad12_g_weights, quad12_weight, quad_order);
   this_quad12 -> physical_position(x_2D_point, xi_2D_point, quad12_x_verts);

   //storing the values for the basis functions
   this_quad12 -> basis(quad12_basis, xi_2D_point, quad12_x_verts);

   // Calling the partial functions
   this_quad12 -> partial_xi_shape_fcn(quad12_partial_xi, xi_2D_point);
   this_quad12 -> partial_eta_shape_fcn(quad12_partial_eta, xi_2D_point);

   //creating matrix of partials
   for (int i = 0; i < quad12_pts; i++){
      quad12_partial[i][0] = quad12_partial_xi[i];
      quad12_partial[i][1] = quad12_partial_eta[i];
   }// end for


   // defining the partials per gauss point
   for (int i = 0; i < tot_q_pts_2d; i++){
      this_quad12 -> partial_xi_shape_fcn(quad12_q_partial_xi[i], quad12_g_pts[i]);
   }

   for (int i = 0; i < tot_q_pts_2d; i++){
      this_quad12 -> partial_eta_shape_fcn(quad12_q_partial_eta[i], quad12_g_pts[i]);
   }

   // creating matrix of Quad 12 quad point partials
   for (int i = 0; i < tot_q_pts_2d; i++){
      for (int j = 0; j < quad12_pts; j++){
         quad12_q_partial[i][j][0] = quad12_q_partial_xi[i][j];
         quad12_q_partial[i][j][1] = quad12_q_partial_eta[i][j];
      } // end for j
   }// end for i

   // calling the jacobian/inverse
   elements::jacobian(quad12_jacobian, quad12_det_j, quad12_x_verts, 
      quad12_partial, quad12_pts, dim_2d);
   elements::jacobian_inverse_2d(quad12_inverse_jacobian, quad12_jacobian);


   // calling the jacobian/inverse for quad points
   for (int i = 0; i < tot_q_pts_2d; i++){
      elements::jacobian(quad12_q_jacobian[i], quad12_q_det_j[i], 
         quad12_x_verts, quad12_q_partial[i], quad12_pts, dim_2d);
   }
   for (int i = 0; i < tot_q_pts_2d; i++){ // looping over the quadrature points
      elements::jacobian_inverse_2d(quad12_q_inverse_jacobian[i], quad12_q_jacobian[i]);
   }
// end of quad 12


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
//
int dim_3d = 3; // dimensions for 3D elements


  /////////////////////////////
  //     Hex 8 element       //
/////////////////////////////// 

   int hex8_pts = 8; // number of nodes
   // call the  hex8 functions

   //call the gauss quadrature functions to set quad points
   elements::Gauss3D(hex8_g_pts, hex8_g_weights, hex8_weight, quad_order);

   this_hex8 -> physical_position(x_point, xi_point, hex8_x_verts);

   //storing the values for the basis functions
   this_hex8 -> basis(hex8_basis, xi_point, hex8_x_verts);

   std::cout << "x location :" << x_point[0] << std::endl;
   std::cout << "y location :" << x_point[1] << std::endl;
   std::cout << "z location :" << x_point[2] << std::endl;
   std::cout << "---" << std::endl;

   //solving the partials for the hex 8 at given point (xi_point)
   this_hex8 -> partial_xi_shape_fcn (hex8_partial_xi,  xi_point);
   this_hex8 -> partial_eta_shape_fcn(hex8_partial_eta, xi_point);
   this_hex8 -> partial_mu_shape_fcn (hex8_partial_mu,  xi_point);

   //Creating matrix of hex 8 partials at a point(add to class?)
   for (int i = 0; i < hex8_pts ; i++){
      hex8_partial[i][0] = hex8_partial_xi[i];
      hex8_partial[i][1] = hex8_partial_eta[i];
      hex8_partial[i][2] = hex8_partial_mu[i];
   } // end for

   // solving for partials at quadrature points for hex8
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex8 -> partial_xi_shape_fcn(hex8_q_partial_xi[i], hex8_g_pts[i]);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex8 -> partial_eta_shape_fcn(hex8_q_partial_eta[i], hex8_g_pts[i]);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex8 -> partial_mu_shape_fcn(hex8_q_partial_mu[i], hex8_g_pts[i]);
   }

   //Combining hex8 partials at quad points (quad_pt, node position, Xi/Eta/Mu)
   for (int i = 0; i < tot_q_pts_3d; i++){
     for (int j = 0; j < hex8_pts; j++){
        hex8_q_partial[i][j][0] = hex8_q_partial_xi[i][j];
        hex8_q_partial[i][j][1] = hex8_q_partial_eta[i][j];
        hex8_q_partial[i][j][2] = hex8_q_partial_mu[i][j];
      } // end for hex8 pts
   } // end for tot_q_pts

   // calling the jacobian and inverse jacobian functions for set point
   elements::jacobian(hex8_jacobian, hex8_det_j, hex8_x_verts, hex8_partial, hex8_pts, dim_3d);
   elements::jacobian_inverse_3d(hex8_inverse_jacobian, hex8_jacobian);

   // calling the jacobian and inverse jacobian functions for quadrature points
   for (int i = 0; i < tot_q_pts_3d; i++){
      elements::jacobian(hex8_q_jacobian[i], hex8_q_det_j[i], hex8_x_verts, 
         hex8_q_partial[i], hex8_pts, dim_3d);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){ // looping over the quadrature points
      elements::jacobian_inverse_3d(hex8_q_inverse_jacobian[i], hex8_q_jacobian[i]);
   }
// end of hex 8

  /////////////////////////////
  //     Hex 20 element      //
/////////////////////////////// 
   int hex20_pts = 20;

   // call the hex20 functions

   //call the gauss quadrature functions to set points/g_weights
   elements::Gauss3D(hex20_g_pts, hex20_g_weights, hex20_weight, quad_order);

   this_hex20 -> physical_position(x_point, xi_point, hex20_x_verts);

   //storing the values for the basis functions
   this_hex20 -> basis(hex20_basis, xi_point, hex20_x_verts);

   // outputting x_point locations
   std::cout << "x location :" << x_point[0] << std::endl;
   std::cout << "y location :" << x_point[1] << std::endl;
   std::cout << "z location :" << x_point[2] << std::endl;
   std::cout << "---" << std::endl;
   
   //defining the hex 20 partials
   this_hex20 -> partial_xi_shape_fcn (hex20_partial_xi,  xi_point); 
   this_hex20 -> partial_eta_shape_fcn(hex20_partial_eta, xi_point);
   this_hex20 -> partial_mu_shape_fcn (hex20_partial_mu,  xi_point); 

   //Creating matrix of hex 20 partials
   for (int i = 0; i < 20; i++){
      hex20_partial[i][0] = hex20_partial_xi[i];
      hex20_partial[i][1] = hex20_partial_eta[i];
      hex20_partial[i][2] = hex20_partial_mu[i];
   }// end for
   
   // solving for partials at quadrature points for hex8
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex20 -> partial_xi_shape_fcn(hex20_q_partial_xi[i], hex20_g_pts[i]);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex20 -> partial_eta_shape_fcn(hex20_q_partial_eta[i], hex20_g_pts[i]);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex20 -> partial_mu_shape_fcn(hex20_q_partial_mu[i], hex20_g_pts[i]);
   }

   // creating matrix of hex 20 quad point partials
   for (int i = 0; i < tot_q_pts_3d; i++){ // looping over the quadrature points
      for (int j = 0; j < 20; j++){ // looping over the nodes
         hex20_q_partial[i][j][0] = hex20_q_partial_xi[i][j];
         hex20_q_partial[i][j][1] = hex20_q_partial_eta[i][j];
         hex20_q_partial[i][j][2] = hex20_q_partial_mu[i][j];
      } // end for j
   }

   //Calling Jacobian and inverse jacobian functions
   elements::jacobian(hex20_jacobian, hex20_det_j, hex20_x_verts, hex20_partial, 
      hex20_pts, dim_3d);
   elements::jacobian_inverse_3d(hex20_inverse_jacobian, hex20_jacobian);


   // calling the jacobian and inverse jacobian functions for quadrature points
   for (int i = 0; i < tot_q_pts_3d; i++){ // looping over the quadrature points
      elements::jacobian(hex20_q_jacobian[i], hex20_q_det_j[i], hex20_x_verts, 
         hex20_q_partial[i],  hex20_pts, dim_3d);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){ // looping over the quadrature points
      elements::jacobian_inverse_3d(hex20_q_inverse_jacobian[i], hex20_q_jacobian[i]);
   }
// end of hex 20

  /////////////////////////////
  //     Hex 32 element      //
///////////////////////////////

   int hex32_pts = 32;

   // call the hex32 functions

   //call the gauss quadrature functions to set points/g_weights
   elements::Gauss3D(hex32_g_pts, hex32_g_weights, hex32_weight, quad_order);

   this_hex32 -> physical_position(x_point, xi_point, hex32_x_verts);

   //storing the values for the basis functions
   this_hex32 -> basis(hex32_basis, xi_point, hex32_x_verts);

   // outputting x_point locations
   std::cout << "x location :" << x_point[0] << std::endl;
   std::cout << "y location :" << x_point[1] << std::endl;
   std::cout << "z location :" << x_point[2] << std::endl;
   std::cout << "---" << std::endl;
   
   //defining the hex 32 partials
   this_hex32 -> partial_xi_shape_fcn (hex32_partial_xi,  xi_point); 
   this_hex32 -> partial_eta_shape_fcn(hex32_partial_eta, xi_point);
   this_hex32 -> partial_mu_shape_fcn (hex32_partial_mu,  xi_point); 

   //Creating matrix of hex 32 partials
   for (int i = 0; i < 32; i++){
      hex32_partial[i][0] = hex32_partial_xi[i];
      hex32_partial[i][1] = hex32_partial_eta[i];
      hex32_partial[i][2] = hex32_partial_mu[i];
   }// end for
   
   // solving for partials at quadrature points for hex8
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex32 -> partial_xi_shape_fcn(hex32_q_partial_xi[i], hex32_g_pts[i]);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex32 -> partial_eta_shape_fcn(hex32_q_partial_eta[i], hex32_g_pts[i]);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){
      this_hex32 -> partial_mu_shape_fcn(hex32_q_partial_mu[i], hex32_g_pts[i]);
   }

   // creating matrix of hex 32 quad point partials
   for (int i = 0; i < tot_q_pts_3d; i++){ // looping over the quadrature points
      for (int j = 0; j < 32; j++){ // looping over the nodes
         hex32_q_partial[i][j][0] = hex32_q_partial_xi[i][j];
         hex32_q_partial[i][j][1] = hex32_q_partial_eta[i][j];
         hex32_q_partial[i][j][2] = hex32_q_partial_mu[i][j];
      } // end for j
   }

   //Calling Jacobian and inverse jacobian functions
   elements::jacobian(hex32_jacobian, hex32_det_j, hex32_x_verts, hex32_partial, 
      hex32_pts, dim_3d);
   elements::jacobian_inverse_3d(hex32_inverse_jacobian, hex32_jacobian);

   // calling the jacobian and inverse jacobian functions for quadrature points
   for (int i = 0; i < tot_q_pts_3d; i++){ // looping over the quadrature points
      elements::jacobian(hex32_q_jacobian[i], hex32_q_det_j[i], hex32_x_verts, 
         hex32_q_partial[i],  hex32_pts, dim_3d);
   }
   for (int i = 0; i < tot_q_pts_3d; i++){ // looping over the quadrature points
      elements::jacobian_inverse_3d(hex32_q_inverse_jacobian[i], hex32_q_jacobian[i]);
   }
// end of Hex 32


/*  ______  _                                _   
   |  ____|| |                              | |  
   | |__   | |  ___  _ __ ___    ___  _ __  | |_ 
   |  __|  | | / _ \| '_ ` _ \  / _ \| '_ \ | __|
   | |____ | ||  __/| | | | | ||  __/| | | || |_ 
   |______||_| \___||_| |_| |_| \___||_| |_| \__|
     _____  _                  _                 
    / ____|| |                | |                
   | |     | |__    ___   ___ | | __ ___         
   | |     | '_ \  / _ \ / __|| |/ // __|        
   | |____ | | | ||  __/| (__ |   < \__ \        
    \_____||_| |_| \___| \___||_|\_\|___/  
*/


// set true to run element checks
bool Q4_check  = true; //Quad 4  checks
bool Q8_check  = true; //Quad 8  checks
bool Q12_check = true; //Quad 12 checks
bool H8_check  = true; //Hex  8  checks
bool H20_check = true; //Hex  20 checks
bool H32_check = true; //Hex  32 checks

// debuging block


std::cout<<std::endl;
std::cout<< "///////////////////////"<<std::endl;
std::cout<< "// Checking Elements //"<<std::endl;
std::cout<< "///////////////////////"<<std::endl;
std::cout<<std::endl;


if(Q4_check){
  /////////////////////////////
  //     Quad 4 element      //
///////////////////////////////

   std::cout<<std::endl;
   std::cout<< "Quad 4 element check"<<std::endl;
   std::cout<< "--------------------"<<std::endl;
   std::cout<<std::endl;
   
   real_t sum_p_xi   = 0.0;
   real_t sum_p_eta  = 0.0;  
   real_t integral   = 0.0;
   real_t partialSumXi  = 0.0;
   real_t partialSumEta = 0.0;
   real_t unity_check = 0.0;
   vector<real_t> taylorQ4(tot_q_pts_2d);

   //checking partition of unity
   
   for(int this_vert = 0; this_vert < 4; this_vert++){
      unity_check += quad4_basis[this_vert];
   }
   std::cout<<"Quad 4 partition of unity:  "<< unity_check << std:: endl;

   // checking sum of Quad 4 partial Xi
   for (int i = 0; i < 4; i ++){
      sum_p_xi += quad4_partial_xi[i];
   }
   std::cout<<"sum of partial Xi--Quad4:  "<< sum_p_xi<<std::endl;

   // checking sum of Quad 4 partials Eta
   for (int i = 0; i < 4; i ++){
     sum_p_eta += quad4_partial_eta[i];
  }
  std::cout<<"sum of partial Eta--Quad4:  "<< sum_p_eta<<std::endl;
  std::cout << std::endl;

   // printing matrix of quad 4 partials 
   // (quad_pt, node position, Xi/Eta/Mu)
  std::cout<<"Quad 4 quad pts partial Derivatives"<< std:: endl;
  std::cout<<"D_Xi  "<< std:: endl;
  for(int i = 0; i < tot_q_pts_2d; i++){
   for(int j = 0; j< 4; j++){
      std::cout<<quad4_q_partial[i][j][0] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

std::cout<<"D_Eta  "<< std:: endl;
for(int i = 0; i < tot_q_pts_2d; i++){
   for(int j = 0; j< 4; j++){
      std::cout<<quad4_q_partial[i][j][1] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 


   // Summing the partials Xi
for (int i = 0; i < tot_q_pts_2d; i++){
   for (int j = 0; j < 4; j++){
      partialSumXi +=  quad4_q_partial_xi[i][j];     
   }
}
std::cout << "quad pts partial Sum Xi: " << partialSumXi << std::endl;

   // Summing the partials Eta
for (int i = 0; i < tot_q_pts_2d; i++){
   for (int j = 0; j < 4; j++){
      partialSumEta +=  quad4_q_partial_eta[i][j];     
   }
}
std::cout << "quad pts partial Sum eta:" << partialSumEta << std::endl;

   // showing the matrix of quad 4 jacobians
std::cout<<"Quad 4 jacobians"<< std::endl;
for(int i = 0; i< 2; i++){
   for(int j = 0; j < 2; j++){
      std::cout<<quad4_jacobian[i][j] << "    ";             
   }
   std::cout << std::endl;
}
std::cout << std::endl;

   // showing the matrix of quad4 inverse jacobians
std::cout<<"Quad4 Jacobian determinant"<< std::endl;
std::cout<<quad4_det_j << "    ";             
std::cout << std::endl;

   // showing the matrix of quad4 inverse jacobians
std::cout<<"Quad4 inverse Jacobian"<< std::endl;
for(int i = 0; i< 2; i++){
   for(int j = 0; j < 2; j++){
      std::cout<<quad4_inverse_jacobian[i][j] << "    ";             
   }
   std::cout << std::endl;
}

   // showing the matrix of quad4 quad point jacobians
std::cout<<"Quad 4 quad point jacobians:"<< std::endl;
for (int q = 0; q < tot_q_pts_2d; q++){
   for(int i = 0; i < 2; i++){
      for(int j = 0; j < 2; j++){
         std::cout<<quad4_q_jacobian[q][i][j] << "    ";             
      }
      std::cout << std::endl;
   }
   std::cout<<std::endl; 
}

   // showing the matrix of quad4 quad point inverse jacobians
std::cout<<"Quad 4 quad point inverse jacobians:"<< std::endl;
for (int q = 0; q < tot_q_pts_2d; q++){
   for(int i = 0; i < 2; i++){
      for(int j = 0; j < 2; j++){
         std::cout<<quad4_q_inverse_jacobian[q][i][j] << "    ";             
      }
      std::cout << std::endl;
   }
   std::cout<<std::endl; 
}

   // Quad 4 integration check
   //printing node locations
std::cout<< "Quad4 nodes"<<std::endl;
for(int this_vert=0; this_vert < quad4_pts; this_vert++){
   for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
      std::cout<<quad4_x_verts[this_vert][this_dim] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

   //combining quad weights and printing
std::cout<< "Quad4 Gauss weights combined"<<std::endl;
for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
   std::cout<<quad4_weight[this_vert]<<std::endl;
}


   // printig gauss point locatons
std::cout<< "Quad4 gauss points in refernece space"<<std::endl;
for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
   for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
      std::cout<<quad4_g_pts[this_vert][this_dim] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

   //Shifting gauss points into real space
for(int this_vert = 0; this_vert < tot_q_pts_2d; this_vert++){
   this_quad4 -> physical_position(quad4_g_pts_real[this_vert], quad4_g_pts[this_vert], quad4_x_verts);  
}

   //Printing gauss points in real space
std::cout<< "Quad4 gauss points real space"<<std::endl;
for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
   for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
      std::cout<<quad4_g_pts_real[this_vert][this_dim] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

   // Create taylor-like nth order polynomial
   // coordinates are of gauss points in real space

for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
   for(int i_order=0; i_order <= n_i; i_order++){
      for(int j_order=0; j_order <= n_j; j_order++){
         taylorQ4[this_vert] += pow(quad4_g_pts_real[this_vert][0],(real_t)i_order) 
         * pow(quad4_g_pts_real[this_vert][1],(real_t)j_order);
      }
   }
}

   //summing to solve integral

for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
   integral += quad4_weight[this_vert]*taylorQ4[this_vert]*quad4_q_det_j[this_vert];
}


std::cout<<"Quad4 order ="<< order <<" test integral = "<<integral<<std::endl;
   // end quad 4 integration check
// end of quad 4
}

if(Q8_check){
  /////////////////////////////
  //     Quad 8 element      //
/////////////////////////////// 

   real_t sum_p_xi   = 0.0;
   real_t sum_p_eta  = 0.0;  
   real_t integral   = 0.0;
   real_t partialSumXi  = 0.0;
   real_t partialSumEta = 0.0;
   real_t unity_check = 0.0;
   vector<real_t> taylorQ8(tot_q_pts_2d);


   std::cout<<std::endl;
   std::cout<< "Quad 8 element check"<<std::endl;
   std::cout<< "--------------------"<<std::endl;
   std::cout<<std::endl;

   //checking partition of unity
   
   for(int this_vert = 0; this_vert < 8; this_vert++){
      unity_check += quad8_basis[this_vert];
   }
   std::cout<<"Quad 8 partition of unity:  "<< unity_check << std:: endl;


   // showing the matrix of Quad12 partials on the screen
   std::cout<<"Quad 8 partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi        D_Eta    "<< std:: endl;
   for(int i = 0; i < 8; i++){
      for(int j = 0; j< 2; j++){
         std::cout<<quad12_partial[i][j] << "    "; 
      }
      std::cout<<i<<std::endl; 
   }
   std::cout<<std::endl; 

   // checking sum of Quad 8 partial Xi

   sum_p_xi = 0;    
   for (int i = 0; i < 8; i ++){
      sum_p_xi += quad8_partial_xi[i];
   }
   std::cout<<"sum of partial xi quad8:  "<< sum_p_xi<<std::endl;

   // checking sum of Quad 8 partials Eta
   sum_p_eta = 0;    
   for (int i = 0; i < 8; i ++){
      sum_p_eta += quad8_partial_eta[i];
   }
   std::cout<<"sum of partial eta quad8:  "<< sum_p_eta<<std::endl;

   // showing the matrix of quad 8 partials on the screen
   // (quad_pt, node position, Xi/Eta/Mu)
   std::cout<<"Quad 8 quad pts partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_2d; i++){
      for(int j = 0; j< 8; j++){
         std::cout<<quad8_q_partial[i][j][0] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   std::cout<<"D_Eta  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_2d; i++){
      for(int j = 0; j< 8; j++){
         std::cout<<quad8_q_partial[i][j][1] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 


   // Summing the partials Xi
   partialSumXi = 0.0;
   for (int i = 0; i < tot_q_pts_2d; i++){
      for (int j = 0; j < 8; j++){
         partialSumXi +=  quad8_q_partial_xi[i][j];     
      }
   }
   std::cout << "quad pts partial Sum Xi: " << partialSumXi << std::endl;

   // Summing the partials Eta
   partialSumEta = 0.0;
   for (int i = 0; i < tot_q_pts_2d; i++){
      for (int j = 0; j < 8; j++){
         partialSumEta +=  quad8_q_partial_eta[i][j];     
      }
   }
   std::cout << "quad pts partial Sum eta:" << partialSumEta << std::endl;

   // showing the matrix of hex 8 jacobians
   std::cout<<std::endl; 
   std::cout<<"Quad 8 jacobians "<< std::endl;
   for(int i = 0; i< 2; i++){
      for(int j = 0; j < 2; j++){
         std::cout<<quad8_jacobian[i][j] << "    ";             
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;

   // showing the matrix of quad4 inverse jacobians
   std::cout<<"Quad8 Jacobian determinant"<< std::endl;
   std::cout<<quad8_det_j << std::endl;             
   std::cout << std::endl;

   // showing the matrix of quad8 inverse jacobians
   std::cout<<std::endl; 
   std::cout<<"Quad8 jacobian inverse"<< std::endl;
   for(int i = 0; i< 2; i++){
      for(int j = 0; j < 2; j++){
         std::cout<<quad8_inverse_jacobian[i][j] << "    ";             
      }
      std::cout << std::endl;
   }

   // showing the matrix of quad4 quad point jacobians
   std::cout<<std::endl;
   std::cout<<"Quad 8 quad point jacobians:"<< std::endl;
   for (int q = 0; q < tot_q_pts_2d; q++){
      for(int i = 0; i < 2; i++){
         for(int j = 0; j < 2; j++){
            std::cout<<quad8_q_jacobian[q][i][j] << "    ";             
         }
         std::cout << std::endl;
      }
      std::cout<<std::endl; 
   }

   // showing the matrix of quad8 quad point inverse jacobians
   std::cout<<"Quad 8 quad point inverse jacobians:"<< std::endl;
   for (int q = 0; q < tot_q_pts_2d; q++){
      for(int i = 0; i < 2; i++){
         for(int j = 0; j < 2; j++){
            std::cout<<quad8_q_inverse_jacobian[q][i][j] << "    ";             
         }
         std::cout << std::endl;
      }
      std::cout<<std::endl; 
   }

   // Quad 8 integration check
   //printing real node locations
   std::cout<< "Quad8 nodes"<<std::endl;
   for(int this_vert=0; this_vert < quad8_pts; this_vert++){
      for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
         std::cout<<quad8_x_verts[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   //combining quad weights and printing
   std::cout<< "Quad8 Gauss weights combined"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      std::cout<<quad8_weight[this_vert]<<std::endl;
   }


   // printig gauss point locatons
   std::cout<< "Quad8 gauss points in refernece space"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
         std::cout<<quad8_g_pts[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   //Shifting gauss points into real space
   for(int this_vert = 0; this_vert < tot_q_pts_2d; this_vert++){
      this_quad8 -> physical_position(quad8_g_pts_real[this_vert], 
       quad8_g_pts[this_vert], quad8_x_verts);  
   }
   
   //Printing gauss points in real space
   std::cout<< "Quad8 gauss points real space"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
         std::cout<<quad8_g_pts_real[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   // Create taylor-like nth order polynomial
   // coordinates are of gauss points in real space

   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      for(int i_order=0; i_order <= n_i; i_order++){
         for(int j_order=0; j_order <= n_j; j_order++){
            taylorQ8[this_vert] += pow(quad8_g_pts_real[this_vert][0],(real_t)i_order) 
            * pow(quad8_g_pts_real[this_vert][1],(real_t)j_order);
         }
      }
   }

   //summing to solve integral
   integral=0.0;

   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      integral += quad8_weight[this_vert]
      * taylorQ8[this_vert]*quad8_q_det_j[this_vert];
   }

   std::cout<<"Quad8 order ="<< order <<" test integral = "<<integral<<std::endl;
   // end quad8 integration check
// end of quad 8 element
}

if(Q12_check){
  /////////////////////////////
  //     Quad 12 element     //
/////////////////////////////// 

   real_t sum_p_xi   = 0.0;
   real_t sum_p_eta  = 0.0;  
   real_t integral   = 0.0;
   real_t partialSumXi  = 0.0;
   real_t partialSumEta = 0.0;
   real_t unity_check = 0.0;
   vector<real_t> taylor12(tot_q_pts_2d);

   std::cout<<std::endl;
   std::cout<< "Quad 12 element check"<<std::endl;
   std::cout<< "--------------------"<<std::endl;
   std::cout<<std::endl;

   sum_p_xi  = 0;
   sum_p_eta = 0; 

   //checking partition of unity
   
   for(int this_vert = 0; this_vert < 12; this_vert++){
      unity_check += quad12_basis[this_vert];
   }
   std::cout<<"Quad 12 partition of unity:  "<< unity_check << std:: endl;

  // showing the matrix of Quad12 partials on the screen
   std::cout<<"Quad 12 partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi        D_Eta    "<< std:: endl;
   for(int i = 0; i < 12; i++){
      for(int j = 0; j< 2; j++){
         std::cout<<quad12_partial[i][j] << "    "; 
      }
      std::cout<<i<<std::endl; 
   }
   std::cout<<std::endl; 

   for (int i = 0; i < 12; i ++){
      sum_p_xi += quad12_partial_xi[i];
   }
   std::cout<<"sum of partial xi quad12:  "<< sum_p_xi<<std::endl;

   // checking sum of Quad 12 partials Eta
   sum_p_eta = 0;    
   for (int i = 0; i < 12; i ++){
      sum_p_eta += quad12_partial_eta[i];
   }
   std::cout<<"sum of partial eta quad12:  "<< sum_p_eta<<std::endl;

   // showing the matrix of quad 12 partials on the screen
   // (quad_pt, node position, Xi/Eta/Mu)
   std::cout<<"Quad 12 quad pts partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_2d; i++){
      for(int j = 0; j< 12; j++){
         std::cout<<quad12_q_partial[i][j][0] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   std::cout<<"D_Eta  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_2d; i++){
      for(int j = 0; j< 12; j++){
         std::cout<<quad12_q_partial[i][j][1] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 


   // Summing the partials Xi
   partialSumXi = 0.0;

   for (int i = 0; i < tot_q_pts_2d; i++){
      for (int j = 0; j < 12; j++){
         partialSumXi +=  quad12_q_partial_xi[i][j];     
      }
   }
   std::cout << "quad pts partial Sum Xi: " << partialSumXi << std::endl;

   // Summing the partials Eta
   partialSumEta = 0.0;
   for (int i = 0; i < tot_q_pts_2d; i++){
      for (int j = 0; j < 12; j++){
         partialSumEta +=  quad12_q_partial_eta[i][j];     
      }
   }
   std::cout << "quad pts partial Sum eta:" << partialSumEta << std::endl;

   // showing the matrix of hex 12 jacobians
   std::cout<<std::endl; 
   std::cout<<"Quad 12 jacobians "<< std::endl;
   for(int i = 0; i< 2; i++){
      for(int j = 0; j < 2; j++){
         std::cout<<quad12_jacobian[i][j] << "    ";             
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;

   // showing the matrix of quad4 inverse jacobians
   std::cout<<"Quad12 Jacobian determinant"<< std::endl;
   std::cout<<quad12_det_j << std::endl;             
   std::cout << std::endl;

   // showing the matrix of quad12 inverse jacobians
   std::cout<<std::endl; 
   std::cout<<"Quad12 jacobian inverse"<< std::endl;
   for(int i = 0; i< 2; i++){
      for(int j = 0; j < 2; j++){
         std::cout<<quad12_inverse_jacobian[i][j] << "    ";             
      }
      std::cout << std::endl;
   }

   // showing the matrix of quad4 quad point jacobians
   std::cout<<std::endl;
   std::cout<<"Quad 12 quad point jacobians:"<< std::endl;
   for (int q = 0; q < tot_q_pts_2d; q++){
      for(int i = 0; i < 2; i++){
         for(int j = 0; j < 2; j++){
            std::cout<<quad12_q_jacobian[q][i][j] << "    ";             
         }
         std::cout << std::endl;
      }
      std::cout<<std::endl; 
   }

   // showing the matrix of quad12 quad point inverse jacobians
   std::cout<<"Quad 12 quad point inverse jacobians:"<< std::endl;
   for (int q = 0; q < tot_q_pts_2d; q++){
      for(int i = 0; i < 2; i++){
         for(int j = 0; j < 2; j++){
            std::cout<<quad12_q_inverse_jacobian[q][i][j] << "    ";             
         }
         std::cout << std::endl;
      }
      std::cout<<std::endl; 
   }


   // Quad 12 integration check
   //printing real node locations
   std::cout<< "Quad12 nodes"<<std::endl;
   for(int this_vert=0; this_vert < quad12_pts; this_vert++){
      for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
         std::cout<<quad12_x_verts[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   //combining quad weights and printing
   std::cout<< "Quad12 Gauss weights combined"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){ 
      std::cout<<quad12_weight[this_vert]<<std::endl;
   }

   // printig gauss point locatons
   std::cout<< "Quad12 gauss points in refernece space"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
         std::cout<<quad12_g_pts[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   //Shifting gauss points into real space
   for(int this_vert = 0; this_vert < tot_q_pts_2d; this_vert++){
      this_quad12 -> physical_position(quad12_g_pts_real[this_vert], 
         quad12_g_pts[this_vert], quad12_x_verts);  
   }
   
   //Printing gauss points in real space
   std::cout<< "Quad12 gauss points real space"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      for(int this_dim = 0; this_dim < dim_2d ; this_dim++){
         std::cout<<quad12_g_pts_real[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   // Create taylor-like nth order polynomial
   // coordinates are of gauss points in real space
   
   vector<real_t> taylorQ12(tot_q_pts_2d);

   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      for(int i_order=0; i_order <= n_i; i_order++){
         for(int j_order=0; j_order <= n_j; j_order++){
            taylorQ12[this_vert] += pow(quad12_g_pts_real[this_vert][0],(real_t)i_order) 
            * pow(quad12_g_pts_real[this_vert][1],(real_t)j_order);
         }
      }
   }

   //summing to solve integral
   integral=0.0;

   for(int this_vert=0; this_vert < tot_q_pts_2d; this_vert++){
      integral += quad12_weight[this_vert]
      * taylorQ12[this_vert] * quad12_q_det_j[this_vert];
   }

   std::cout<<"Quad12 order ="<< order <<" test integral = "<<integral<<std::endl;
   //end quad 12 integration check
// end of quad 12 element
} 

if(H8_check){
  /////////////////////////////
  //     Hex 8 element       //
/////////////////////////////// 


   real_t sum_p_xi   = 0.0;
   real_t sum_p_eta  = 0.0;  
   real_t integral   = 0.0;
   real_t partialSumXi  = 0.0;
   real_t partialSumEta = 0.0;
   real_t partialSumMu  = 0.0;
   real_t unity_check = 0.0;
   vector<real_t> taylorH8(tot_q_pts_3d);

   std::cout<<std::endl;
   std::cout<< "Hex 8 element check"<<std::endl;
   std::cout<< "--------------------"<<std::endl;
   std::cout<<std::endl;

   //checking partition of unity
   
   for(int this_vert = 0; this_vert < 8; this_vert++){
      unity_check += hex8_basis[this_vert];
   }
   std::cout<<"Hex 8 partition of unity:  "<< unity_check << std:: endl;

   //printing out the gauss point locations
   std::cout<< " Hex8 Gauss Point Locations"<< std::endl;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 3; j++){
         std::cout  << std::fixed;
         std::cout<< hex8_g_pts[i][j]<< "   " ;
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;

   //printing out the gauss g_weights
   std::cout<< " Hex8 Gauss Point weights"<< std::endl;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 3; j++){
         std::cout  << std::fixed;
         std::cout<< hex8_g_weights[i][j]<< "   " ;
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;

   // showing the matrix of hex8 partials on the screen
   std::cout<<"Hex 8 partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi        D_Eta        D_Mu"<< std:: endl;
   for(int i = 0; i < 8; i++){
      for(int j = 0; j< 3; j++){
         std::cout<<hex8_partial[i][j] << "    "; 
      }
      std::cout<<i<<std::endl;
   }
   std::cout<<std::endl; 

   // Summing the partials Xi
   partialSumXi = 0.0;
   for (int i = 0; i < 8; i++){
     partialSumXi +=  hex8_partial_xi[i];     
  }
  std::cout << "partial Sum Xi: " << partialSumXi << std::endl;

   // Summing the partials Eta
  partialSumEta = 0.0;
  for (int i = 0; i < 8; i++){
   partialSumEta +=  hex8_partial_eta[i];     
}
std::cout << "partial Sum eta:" << partialSumEta << std::endl;

   // Summing the partials Mu

for (int i = 0; i < 8; i++){
   partialSumMu +=  hex8_partial_mu[i];     
}
std::cout << "partial Sum Mu: " << partialSumMu << std::endl;
std::cout<<std::endl; 


   // showing the matrix of hex8 partials on the screen
   // (quad_pt, node position, Xi/Eta/Mu)
std::cout<<"Hex 8 quad pts partial Derivatives"<< std:: endl;
std::cout<<"D_Xi  "<< std:: endl;
for(int i = 0; i < tot_q_pts_3d; i++){
   for(int j = 0; j< 8; j++){
      std::cout<<hex8_q_partial[i][j][0] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

std::cout<<"D_Eta  "<< std:: endl;
for(int i = 0; i < tot_q_pts_3d; i++){
   for(int j = 0; j< 8; j++){
      std::cout<<hex8_q_partial[i][j][1] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

std::cout<<"D_Mu  "<< std:: endl;
for(int i = 0; i < tot_q_pts_3d; i++){
   for(int j = 0; j< 8; j++){
      std::cout<<hex8_q_partial[i][j][2] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 


   // Summing the partials Xi
partialSumXi = 0.0;
for (int i = 0; i <tot_q_pts_3d; i++){
   for (int j = 0; j < 8; j++){
      partialSumXi +=  hex8_q_partial_xi[i][j];     
   }
}
std::cout << "quad pts partial Sum Xi: " << partialSumXi << std::endl;

   // Summing the partials Eta
partialSumEta = 0.0;
for (int i = 0; i < tot_q_pts_3d; i++){
   for (int j = 0; j < 8; j++){
      partialSumEta +=  hex8_q_partial_eta[i][j];     
   }
}
std::cout << "quad pts partial Sum eta:" << partialSumEta << std::endl;

   // Summing the partials Mu
partialSumMu = 0.0;
for (int i = 0; i < tot_q_pts_3d; i++){
   for (int j = 0; j < 8; j++){
     partialSumMu +=  hex8_q_partial_mu[i][j];   
  }
}
std::cout << "quad pts partial Sum Mu: " << partialSumMu << std::endl;
std::cout<<std::endl; 

   // showing the matrix of hex8 jacobians
std::cout<<"Hex 8 jacobians:"<< std::endl;
for(int i = 0; i< 3; i++){
   for(int j = 0; j < 3; j++){
      std::cout<<hex8_jacobian[i][j] << "    ";             
   }
   std::cout << std::endl;
}
std::cout<<std::endl; 

   // showing the matrix of quad4 inverse jacobians
std::cout<<"Hex8 Jacobian determinant"<< std::endl;
std::cout<<hex8_det_j << std::endl;             

   // showing the matrix of hex8 inverse jacobians
std::cout<<"Hex 8 inverse jacobian"<< std::endl;
for(int i = 0; i< 3; i++){
   for(int j = 0; j < 3; j++){
      std::cout<<hex8_inverse_jacobian[i][j] << "    ";             
   }
   std::cout << std::endl;
}
std::cout<<std::endl; 

   // showing the matrix of hex8 quad point jacobians
std::cout<<"Hex 8 quad point jacobians:"<< std::endl;
for (int q = 0; q < tot_q_pts_3d; q++){
   for(int i = 0; i < 3; i++){
     for(int j = 0; j < 3; j++){
      std::cout<<hex8_q_jacobian[q][i][j] << "    ";             
   }
   std::cout << std::endl;
}
std::cout<<std::endl; 
}

   // showing the matrix of hex8 quad point inverse jacobians
std::cout<<"Hex 8 quad point inverse jacobians:"<< std::endl;
for (int q = 0; q < tot_q_pts_3d; q++){
   for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
         std::cout<<hex8_q_inverse_jacobian[q][i][j] << "    ";             
      }
      std::cout << std::endl;
   }
   std::cout<<std::endl; 
}



   // checking that dot prodct of magnitude of partials
   // and magnitude of position of node is 1

   // for hex 8 element
real_t mag_hex8_verts[8];
real_t mag_hex8_partial[8];

   // magnitude of vector to verts from center
for (int i = 0; i < 8; i++) {
   mag_hex8_verts[i] = sqrt((hex8_x_verts[i][0]*hex8_x_verts[i][0])
      + (hex8_x_verts[i][1]*hex8_x_verts[i][1])
      + (hex8_x_verts[i][2]*hex8_x_verts[i][2]));
}

   //magnitude of partials at each vertex
for (int i = 0; i < 8; i++) {
   mag_hex8_partial[i] = sqrt((hex8_partial[i][0]*hex8_partial[i][0])
    + (hex8_partial[i][1]*hex8_partial[i][1])
    + (hex8_partial[i][2]*hex8_partial[i][2]));
}

   //creating unit vectors to verts
real_t hex8_ehat_p_mag[8][3];
for (int i = 0; i < 8; i++){
   hex8_ehat_p_mag[i][0] = hex8_x_verts[i][0]/mag_hex8_verts[i];
   hex8_ehat_p_mag[i][1] = hex8_x_verts[i][1]/mag_hex8_verts[i];
   hex8_ehat_p_mag[i][2] = hex8_x_verts[i][2]/mag_hex8_verts[i];
}

   // creating unit vectors of partials at nodes
real_t hex8_del_phi[8][3];
for (int i = 0; i < 8; i++){
   hex8_del_phi[i][0] = hex8_partial[i][0]/mag_hex8_partial[i];
   hex8_del_phi[i][1] = hex8_partial[i][1]/mag_hex8_partial[i];
   hex8_del_phi[i][2] = hex8_partial[i][2]/mag_hex8_partial[i];
}

   //calculating dot product for hex 8 vectors
real_t dot_hex8_vec[8];
for(int i = 0; i < 8; i++){
   dot_hex8_vec[i] = (hex8_ehat_p_mag[i][0])*(hex8_del_phi[i][0])
   + (hex8_ehat_p_mag[i][1])*(hex8_del_phi[i][1])
   + (hex8_ehat_p_mag[i][2])*(hex8_del_phi[i][2]);
}

std::cout<<"dot product of hex 8 vectors:"<< std::endl;
for(int i = 0; i < 8; i++){
   std::cout<< dot_hex8_vec[i]<< std::endl;
}

   //Hex 8 integration check
   //printing node locations
std::cout<< "Hex8 nodes"<<std::endl;
for(int this_vert=0; this_vert < hex8_pts; this_vert++){
   for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
      std::cout<<hex8_x_verts[this_vert][this_dim] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

   //combining quad weights and printing
std::cout<< "Hex8 Gauss weights combined"<<std::endl;
for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
   std::cout<<hex8_weight[this_vert]<<std::endl;
}

   // printig gauss point locatons
std::cout<< "Hex8 gauss points in refernece space"<<std::endl;
for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
   for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
      std::cout<<hex8_g_pts[this_vert][this_dim] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

   //Shifting gauss points into real space
for(int this_vert = 0; this_vert < tot_q_pts_3d; this_vert++){
   this_hex8 -> physical_position(hex8_g_pts_real[this_vert], 
     hex8_g_pts[this_vert], hex8_x_verts);  
}

   //Printing gauss points in real space
std::cout<< "Hex8 gauss points real space"<<std::endl;
for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
   for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
      std::cout<<hex8_g_pts_real[this_vert][this_dim] << "    "; 
   }
   std::cout<<std::endl; 
}
std::cout<<std::endl; 

   // Create taylor-like nth order polynomial
   // coordinates are of gauss points in real space

for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
   for(int i_order=0; i_order <= n_i; i_order++){
      for(int j_order=0; j_order <= n_j; j_order++){
         for(int k_order=0; k_order <= n_k; k_order++){
            taylorH8[this_vert] += pow(hex8_g_pts_real[this_vert][0],(real_t)i_order) 
            * pow(hex8_g_pts_real[this_vert][1],(real_t)j_order)
            * pow(hex8_g_pts_real[this_vert][3],(real_t)k_order);
         }
      }
   }
}

   //summing to solve integral

for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
   integral += hex8_weight[this_vert]
   * taylorH8[this_vert]*hex8_q_det_j[this_vert];
}

std::cout<<"Hex8 order ="<< order <<" test integral = "<<integral<<std::endl;
   // end Hex8 integration check
// end of hex8 element checks
}

if(H20_check){
  /////////////////////////////
  //     Hex 20 element      //
/////////////////////////////// 

   real_t sum_p_xi   = 0.0;
   real_t sum_p_eta  = 0.0;  
   real_t integral   = 0.0;
   real_t partialSumXi  = 0.0;
   real_t partialSumEta = 0.0;
   real_t partialSumMu  = 0.0;
   real_t unity_check = 0.0;
   vector<real_t> taylorH20(tot_q_pts_3d);


   std::cout<<std::endl;
   std::cout<< "Hex 20 element check"<<std::endl;
   std::cout<< "--------------------"<<std::endl;
   std::cout<<std::endl;

   //checking partition of unity
   
   for(int this_vert = 0; this_vert < 20; this_vert++){
      unity_check += hex20_basis[this_vert];
   }
   std::cout<<"Hex 20 partition of unity:  "<< unity_check << std:: endl;

   
   //printing out the gauss point locations
   std::cout<< " Hex20 Gauss Point Locations"<< std::endl;

   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 3; j++){
         std::cout  << std::fixed;
         std::cout<< hex20_g_pts[i][j]<< "   " ;
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;

   //printing out the gauss weights
   std::cout<< " Hex20 Gauss Point weights"<< std::endl;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 3; j++){
         std::cout  << std::fixed;
         std::cout<< hex20_g_weights[i][j]<< "   " ;
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;
   
   // showing the matrix of hex20 partials on the screen
   std::cout<<"Hex 20 partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi        D_Eta        D_Mu"<< std:: endl;
   for(int i = 0; i < 20; i++){
      for(int j = 0; j< 3; j++){
         std::cout<<hex20_partial[i][j] << "    "; 
      }
      std::cout<<i<<std::endl; 
   }


   // Summing the partials Xi
   std::cout << std::endl;
   partialSumXi = 0.0;
   for (int i = 0; i < 20; i++){
      partialSumXi +=  hex20_partial_xi[i];    
   }
   std::cout << "partial Sum Xi: " << partialSumXi << std::endl;

   // Summing the partials Eta
   partialSumEta = 0.0;
   for (int i = 0; i < 20; i++){
      partialSumEta +=  hex20_partial_eta[i];    
   }
   std::cout << "partial Sum Eta: " << partialSumEta << std::endl;

   // Summing the partials Mu
   partialSumMu = 0.0;
   for (int i = 0; i < 20; i++){
      partialSumMu +=  hex20_partial_mu[i];    
   }
   std::cout << "partial Sum Mu: " << partialSumMu << std::endl;

   // showing the matrix of hex20 jacobians
   std::cout << std::endl;
   std::cout<<"Hex 20 jacobian"<< std::endl;
   for(int i = 0; i< 3; i++){
      for(int j = 0; j < 3; j++){
         std::cout<<hex20_jacobian[i][j] << "  ";             
      }
      std::cout << std::endl;
   }

   // showing the matrix of quad4 inverse jacobians
   std::cout << std::endl;
   std::cout<<"Hex20 Jacobian determinant"<< std::endl;
   std::cout<<hex20_det_j << std::endl;             


   // showing the matrix of hex20 inverse jacobians
   std::cout << std::endl;
   std::cout<<"Hex 20 jacobian inverse"<< std::endl;
   for(int i = 0; i< 3; i++){
      for(int j = 0; j < 3; j++){
         std::cout<<hex20_inverse_jacobian[i][j] << "    ";             
      }
      std::cout << std::endl;
   } 

   // showing the matrix of hex8 partials on the screen
   // (quad_pt, node position, Xi/Eta/Mu)
   std::cout<<"Hex 20 quad pts partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_3d; i++){
      for(int j = 0; j< 20; j++){
         std::cout<<hex20_q_partial[i][j][0] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   std::cout<<"D_Eta  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_3d; i++){
      for(int j = 0; j< 20; j++){
         std::cout<<hex20_q_partial[i][j][1] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   std::cout<<"D_Mu  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_3d; i++){
      for(int j = 0; j< 20; j++){
         std::cout<<hex20_q_partial[i][j][2] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   // Summing the partials Xi
   partialSumXi = 0.0;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 20; j++){
         partialSumXi = partialSumXi + hex20_q_partial_xi[i][j];     
      }
   }
   std::cout << "quad pts partial Sum Xi: " << partialSumXi << std::endl;
   
   // Summing the partials Eta
   partialSumEta = 0.0;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 20; j++){
         partialSumEta +=  hex20_q_partial_eta[i][j];     
      }
   }
   std::cout << "quad pts partial Sum eta:" << partialSumEta << std::endl;

   partialSumMu = 0.0;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 20; j++){
         partialSumMu +=  hex20_q_partial_mu[i][j];   
      }
   }
   std::cout << "quad pts partial Sum Mu: " << partialSumMu << std::endl;
   std::cout<<std::endl; 

   // showing the matrix of hex20 quad point jacobians
   std::cout<<"Hex 20 quad point jacobians:"<< std::endl;
   for (int q = 0; q < tot_q_pts_3d; q++){
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
            std::cout<<hex20_q_jacobian[q][i][j] << "    ";             
         }
         std::cout << std::endl;
      }
      std::cout<<std::endl; 
   }

   // showing the matrix of hex20 quad point inverse jacobians
   std::cout<<"Hex 20 quad point inverse jacobians:"<< std::endl;
   for (int q = 0; q < tot_q_pts_3d; q++){
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
            std::cout<<hex20_q_inverse_jacobian[q][i][j] << "    ";             
         }
         std::cout << std::endl;
      }
      std::cout<<std::endl; 
   }

   // checking that dot prodct of magnitude of partials
   // and magnitude of position of node is 1

   real_t mag_hex20_verts[20];
   real_t mag_hex20_partial[20];

   // magnitude of vector to verts from center
   for (int i = 0; i < 20; i++) {
      mag_hex20_verts[i] = sqrt((hex20_x_verts[i][0]*hex20_x_verts[i][0])
         + (hex20_x_verts[i][1]*hex20_x_verts[i][1])
         + (hex20_x_verts[i][2]*hex20_x_verts[i][2]));
   }

   //magnitude of partials at each vertex
   for (int i = 0; i < 20; i++) {
      mag_hex20_partial[i] = sqrt((hex20_partial[i][0]*hex20_partial[i][0])
       + (hex20_partial[i][1]*hex20_partial[i][1])
       + (hex20_partial[i][2]*hex20_partial[i][2]));
   }

   //creating unit vectors to verts
   real_t hex20_ehat_p_mag[20][3];

   for (int i = 0; i < 20; i++){
      hex20_ehat_p_mag[i][0] = hex20_x_verts[i][0]/mag_hex20_verts[i];
      hex20_ehat_p_mag[i][1] = hex20_x_verts[i][1]/mag_hex20_verts[i];
      hex20_ehat_p_mag[i][2] = hex20_x_verts[i][2]/mag_hex20_verts[i];
   }


   // creating unit vectos of partials at nodes
   real_t hex20_del_phi[20][3];

   for (int i = 0; i < 20; i++){
      hex20_del_phi[i][0] = hex20_partial[i][0]/mag_hex20_partial[i];
      hex20_del_phi[i][1] = hex20_partial[i][1]/mag_hex20_partial[i];
      hex20_del_phi[i][2] = hex20_partial[i][2]/mag_hex20_partial[i];
   }

   //calculating dot product for hex 20 vectors
   real_t dot_hex20_vec[20];

   for(int i = 0; i < 20; i++){
      dot_hex20_vec[i] = (hex20_ehat_p_mag[i][0])*(hex20_del_phi[i][0])
      + (hex20_ehat_p_mag[i][1])*(hex20_del_phi[i][1])
      + (hex20_ehat_p_mag[i][2])*(hex20_del_phi[i][2]);
   } 


   std::cout<<"dot product of hex 20 vectors:"<< std::endl;
   for(int i = 0; i < 20; i++){
      std::cout<< dot_hex20_vec[i]<< std::endl;
   }

   //Hex 20 integration check
   //printing node locations
   std::cout<< "Hex20 nodes"<<std::endl;
   for(int this_vert=0; this_vert < hex20_pts; this_vert++){
      for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
         std::cout<<hex20_x_verts[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   //combining quad weights and printing
   std::cout<< "Hex20 Gauss weights combined"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){

      std::cout<<hex20_weight[this_vert]<<std::endl;
   }


   // printig gauss point locatons
   std::cout<< "Hex20 gauss points in refernece space"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
      for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
         std::cout<<hex20_g_pts[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   //Shifting gauss points into real space
   for(int this_vert = 0; this_vert < tot_q_pts_3d; this_vert++){
      this_hex20 -> physical_position(hex20_g_pts_real[this_vert],
       hex20_g_pts[this_vert], hex20_x_verts);  
   }
   
   //Printing gauss points in real space
   std::cout<< "Hex20 gauss points real space"<<std::endl;
   for(int this_vert = 0; this_vert < tot_q_pts_3d; this_vert++){
      for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
         std::cout<<hex20_g_pts_real[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   // Create taylor-like nth order polynomial
   // coordinates are of gauss points in real space

   for(int this_vert = 0; this_vert < tot_q_pts_3d; this_vert++){
      for(int i_order = 0; i_order <= n_i; i_order++){
         for(int j_order = 0; j_order <= n_j; j_order++){
            for(int k_order = 0; k_order <= n_k; k_order++){
               taylorH20[this_vert] += pow(hex20_g_pts_real[this_vert][0],(real_t)i_order) 
               * pow(hex20_g_pts_real[this_vert][1],(real_t)j_order)
               * pow(hex20_g_pts_real[this_vert][2],(real_t)k_order);
            }
         }
      }
   }

   //summing to solve integral
   integral=0.0;

   for(int this_vert = 0; this_vert < tot_q_pts_3d; this_vert++){
      integral += hex20_weight[this_vert]*taylorH20[this_vert]
      * hex20_q_det_j[this_vert];
   }

   std::cout<<"Hex20 order ="<< order <<" test integral = "<<integral<<std::endl;
   // end Hex20 integration check
// end of hex 20
}

if(H32_check){
  /////////////////////////////
  //     Hex 32 element      //
///////////////////////////////

   std::cout<<std::endl;
   std::cout<< "Hex 32 element check"<<std::endl;
   std::cout<< "--------------------"<<std::endl;
   std::cout<<std::endl;

   real_t sum_p_xi   = 0.0;
   real_t sum_p_eta  = 0.0;  
   real_t integral   = 0.0;
   real_t partialSumXi  = 0.0;
   real_t partialSumEta = 0.0;
   real_t partialSumMu  = 0.0;
   real_t unity_check = 0.0;
   vector<real_t> taylorH32(tot_q_pts_3d);

   //checking partition of unity
   
   for(int this_vert = 0; this_vert < 32; this_vert++){
      unity_check += hex32_basis[this_vert];
   }
   std::cout<<"Hex 32 partition of unity:  "<< unity_check << std:: endl;

   //printing out the gauss point locations
   std::cout<< " Hex32 Gauss Point Locations"<< std::endl;

   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 3; j++){
         std::cout  << std::fixed;
         std::cout<< hex32_g_pts[i][j]<< "   " ;
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;

   //printing out the gauss weights
   std::cout<< " Hex32 Gauss Point weights"<< std::endl;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 3; j++){
         std::cout  << std::fixed;
         std::cout<< hex32_g_weights[i][j]<< "   " ;
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;
   
   // showing the matrix of hex32 partials on the screen
   std::cout<<"Hex 32 partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi        D_Eta        D_Mu"<< std:: endl;
   for(int i = 0; i < 32; i++){
      for(int j = 0; j< 3; j++){
         std::cout<<hex32_partial[i][j] << "    "; 
      }
      std::cout<<i<<std::endl; 
   }


   // Summing the partials Xi
   std::cout << std::endl;
   partialSumXi = 0.0;
   for (int i = 0; i < 32; i++){
      partialSumXi +=  hex32_partial_xi[i];    
   }
   std::cout << "partial Sum Xi: " << partialSumXi << std::endl;

   // Summing the partials Eta
   partialSumEta = 0.0;
   for (int i = 0; i < 32; i++){
      partialSumEta +=  hex32_partial_eta[i];    
   }
   std::cout << "partial Sum Eta: " << partialSumEta << std::endl;

   // Summing the partials Mu
   partialSumMu = 0.0;
   for (int i = 0; i < 32; i++){
      partialSumMu +=  hex32_partial_mu[i];    
   }
   std::cout << "partial Sum Mu: " << partialSumMu << std::endl;

   // showing the matrix of hex32 jacobians
   std::cout << std::endl;
   std::cout<<"Hex 32 jacobian"<< std::endl;
   for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
         std::cout<<hex32_jacobian[i][j] << "  ";             
      }
      std::cout << std::endl;
   }

   // showing the matrix of quad4 inverse jacobians
   std::cout << std::endl;
   std::cout<<"Hex32 Jacobian determinant"<< std::endl;
   std::cout<<hex32_det_j << std::endl;             


   // showing the matrix of hex32 inverse jacobians
   std::cout << std::endl;
   std::cout<<"Hex 32 jacobian inverse"<< std::endl;
   for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
         std::cout<<hex32_inverse_jacobian[i][j] << "    ";             
      }
      std::cout << std::endl;
   } 

   // showing the matrix of hex8 partials on the screen
   // (quad_pt, node position, Xi/Eta/Mu)
   std::cout<<"Hex 32 quad pts partial Derivatives"<< std:: endl;
   std::cout<<"D_Xi  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_3d; i++){
      for(int j = 0; j< 32; j++){
         std::cout<<hex32_q_partial[i][j][0] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   std::cout<<"D_Eta  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_3d; i++){
      for(int j = 0; j< 32; j++){
         std::cout<<hex32_q_partial[i][j][1] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   std::cout<<"D_Mu  "<< std:: endl;
   for(int i = 0; i < tot_q_pts_3d; i++){
      for(int j = 0; j< 32; j++){
         std::cout<<hex32_q_partial[i][j][2] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   // Summing the partials Xi
   partialSumXi = 0.0;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 32; j++){
         partialSumXi = partialSumXi + hex32_q_partial_xi[i][j];     
      }
   }
   std::cout << "quad pts partial Sum Xi: " << partialSumXi << std::endl;
   
   // Summing the partials Eta
   partialSumEta = 0.0;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 32; j++){
         partialSumEta +=  hex32_q_partial_eta[i][j];     
      }
   }
   std::cout << "quad pts partial Sum eta:" << partialSumEta << std::endl;

   partialSumMu = 0.0;
   for (int i = 0; i < tot_q_pts_3d; i++){
      for (int j = 0; j < 32; j++){
         partialSumMu += hex32_q_partial_mu[i][j];   
      }
   }
   std::cout << "quad pts partial Sum Mu: " << partialSumMu << std::endl;
   std::cout<<std::endl; 

   // showing the matrix of hex32 quad point jacobians
   std::cout<<"Hex 32 quad point jacobians:"<< std::endl;
   for (int q = 0; q < tot_q_pts_3d; q++){
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
            std::cout<<hex32_q_jacobian[q][i][j] << "    ";             
         }
         std::cout << std::endl;
      }
      std::cout<<std::endl; 
   }

   // showing the matrix of hex32 quad point inverse jacobians
   std::cout<<"Hex 32 quad point inverse jacobians:"<< std::endl;
   for (int q = 0; q < tot_q_pts_3d; q++){
      for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
            std::cout<<hex32_q_inverse_jacobian[q][i][j] << "    ";             
         }
         std::cout << std::endl;
      }
      std::cout<<std::endl; 
   }

   // checking that the dot prodct of magnitude of partials
   // and magnitude of position of node is 1

   real_t mag_hex32_verts[32];
   real_t mag_hex32_partial[32];

   // magnitude of vector to verts from center
   for (int i = 0; i < 32; i++) {
      mag_hex32_verts[i] = sqrt((hex32_x_verts[i][0]*hex32_x_verts[i][0])
         + (hex32_x_verts[i][1]*hex32_x_verts[i][1])
         + (hex32_x_verts[i][2]*hex32_x_verts[i][2]));
   }

   //magnitude of partials at each vertex
   for (int i = 0; i < 32; i++) {
      mag_hex32_partial[i] = sqrt((hex32_partial[i][0]*hex32_partial[i][0])
       + (hex32_partial[i][1]*hex32_partial[i][1])
       + (hex32_partial[i][2]*hex32_partial[i][2]));
   }

   //creating unit vectors to verts
   real_t hex32_ehat_p_mag[32][3];

   for (int i = 0; i < 32; i++){
      hex32_ehat_p_mag[i][0] = hex32_x_verts[i][0]/mag_hex32_verts[i];
      hex32_ehat_p_mag[i][1] = hex32_x_verts[i][1]/mag_hex32_verts[i];
      hex32_ehat_p_mag[i][2] = hex32_x_verts[i][2]/mag_hex32_verts[i];
   }


   // creating unit vectos of partials at nodes
   real_t hex32_del_phi[32][3];

   for (int i = 0; i < 32; i++){
      hex32_del_phi[i][0] = hex32_partial[i][0]/mag_hex32_partial[i];
      hex32_del_phi[i][1] = hex32_partial[i][1]/mag_hex32_partial[i];
      hex32_del_phi[i][2] = hex32_partial[i][2]/mag_hex32_partial[i];
   }

   //calculating dot product for hex 32 vectors
   real_t dot_hex32_vec[32];

   for(int i = 0; i < 32; i++){
      dot_hex32_vec[i] = (hex32_ehat_p_mag[i][0])*(hex32_del_phi[i][0])
      + (hex32_ehat_p_mag[i][1])*(hex32_del_phi[i][1])
      + (hex32_ehat_p_mag[i][2])*(hex32_del_phi[i][2]);
   } 


   std::cout<<"dot product of hex 32 vectors:"<< std::endl;
   for(int i = 0; i < 32; i++){
      std::cout<< dot_hex32_vec[i]<< std::endl;
   }
   //Hex 32 integration check
   //printing node locations
   std::cout<< "Hex32 nodes"<<std::endl;
   for(int this_vert=0; this_vert < hex32_pts; this_vert++){
      for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
         std::cout<<hex32_x_verts[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   //combining quad weights and printing
   std::cout<< "Hex32 Gauss weights combined"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){ 
      std::cout<<hex32_weight[this_vert]<<std::endl;
   }


   // printig gauss point locatons
   std::cout<< "Hex32 gauss points in refernece space"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
      for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
         std::cout<<hex32_g_pts[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   //Shifting gauss points into real space
   for(int this_vert = 0; this_vert < tot_q_pts_3d; this_vert++){
      this_hex32 -> physical_position(hex32_g_pts_real[this_vert], 
       hex32_g_pts[this_vert], hex32_x_verts);  
   }
   
   //Printing gauss points in real space
   std::cout<< "Hex32 gauss points real space"<<std::endl;
   for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
      for(int this_dim = 0; this_dim < dim_3d ; this_dim++){
         std::cout<<hex32_g_pts_real[this_vert][this_dim] << "    "; 
      }
      std::cout<<std::endl; 
   }
   std::cout<<std::endl; 

   // Create taylor-like nth order polynomial
   // coordinates are of gauss points in real space

   for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
      for(int i_order=0; i_order <= n_i; i_order++){
         for(int j_order=0; j_order <= n_j; j_order++){
            for(int k_order=0; k_order <= n_k; k_order++){
               taylorH32[this_vert] += pow(hex32_g_pts_real[this_vert][0],(real_t)i_order) 
               * pow(hex32_g_pts_real[this_vert][1],(real_t)j_order)
               * pow(hex32_g_pts_real[this_vert][2],(real_t)k_order);
            }
         }
      }
   }

   //summing to solve integral
   integral=0.0;

   for(int this_vert=0; this_vert < tot_q_pts_3d; this_vert++){
      integral += hex32_weight[this_vert]*taylorH32[this_vert]
      * hex32_q_det_j[this_vert];
   }

   std::cout<<"Hex32 order ="<< order <<" test integral = "<<integral<<std::endl;
   // end Hex32 integration check
// end of hex 32
}

}// end  of main function
