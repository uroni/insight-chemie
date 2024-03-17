#include "irrlicht/irrlicht.h"

#ifdef D_DEFINE_RESOURCES
irr::video::ITexture* r_neutron_texture;
irr::scene::IAnimatedMesh* r_neutron_mesh;

irr::video::ITexture* r_proton_texture;
irr::scene::IAnimatedMesh* r_proton_mesh;

irr::video::ITexture* r_elektron_texture;
irr::scene::IAnimatedMesh* r_elektron_mesh;

irr::scene::IAnimatedMesh* r_atom1u_mesh;

irr::video::ITexture* r_bank_texture;
irr::video::ITexture* r_pc_bank_textures[100];

irr::scene::IAnimatedMesh* r_bank_mesh;
irr::scene::IAnimatedMesh* r_bank_dot_mesh;

irr::scene::IAnimatedMesh* r_box1_mesh;

#else if

extern irr::video::ITexture* r_neutron_texture;
extern irr::scene::IAnimatedMesh* r_neutron_mesh;

extern irr::video::ITexture* r_proton_texture;
extern irr::scene::IAnimatedMesh* r_proton_mesh;

extern irr::video::ITexture* r_elektron_texture;
extern irr::scene::IAnimatedMesh* r_elektron_mesh;

extern irr::scene::IAnimatedMesh* r_atom1u_mesh;

extern irr::video::ITexture* r_bank_texture;
extern irr::video::ITexture* r_pc_bank_textures[100];

extern irr::scene::IAnimatedMesh* r_bank_mesh;
extern irr::scene::IAnimatedMesh* r_bank_dot_mesh;

extern irr::scene::IAnimatedMesh* r_box1_mesh;


#endif

