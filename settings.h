#include "irrlicht/irrlicht.h"

#ifdef D_DEFINE_SETTINGS
uchar s_video_driver=0;
_f32 mousescale=0.1f;
_f32 catom_positionscale=10;
_f32 catom_stepsize=1;
_f32 catom_numsteps=100;
_f32 catom_core_phi=0.00001f;
_f32 catom_core_exp=2;
_f32 catom_r_neutron=71;
_f32 catom_r_proton=71;
_f32 catom_core_away=1;
_f32 catom_elektron_startspeed=0.1f;
_f32 catom_core_startforce=1;
_f32 catom_elektron_smoothvalue=1;
_f32 catom_core_coreforcescale=0.00001f;
bool catom_draw_elcoreline=false;
irr::core::vector3df sandboxsize=irr::core::vector3df(5000,5000,5000);
_f32 catom_elektron_force=0.1f;
_f32 catom_bank_coreforcescale=0.00000000001f;
_f32 catom_bank_force=0.01f;
_f32 catom_bank_distance=50;
_f32 catom_connection_forcescale=0.00000000001f;
_f32 catom_inter_connection_forcescale=0.0001f;
_f32 catom_inter_connection_distance_multi=15;
_f32 catom_connection_backdrift=0.001f;
_f32 catom_connection_backdrift_changing=100;
_f32 catom_connection_change_limit=10;
_f32 catom_connection_centerscale=10;
_f32 catom_connection_size=10;
_f32 catom_connection_length=0.1f;
_f32 catom_connection_max_sensibility=0.1f;
_f32 time_cap=300;
_f32 catom_connection2bank_force=0.02f; // 2*catom_connection2connection_force
_f32 catom_connection2connection_force=0.01f;
_f32 catom_banks_distance_cap=1000;
_f32 catom_banks_near_distance_cap=1;
_f32 catom_bank2connection_force=0.01f;
_i32 catom_change_cap=100000; // the greater the better
_i32 catom_freezetime=100;
_f32 catom2catom_force_scale=0.01f;
_f32 catom2catom_distance_cap=100;
_i32 catom_allow_freeze=1;
_f32 mouse_wheel_unit=10;
_f32 camera_default_distance=1000;
_f32 camera_mouse_scale=0.1;
_f32 catom_connection_visible_distance=1000;
_f32 catom_connection_transparent_distance=10000;
_f32 camera_position_center_speed=0.001f;
_f32 camera_target_center_speed=0.001f;
_f32 camera_zoom_scale=10;
_f32 camera_zoom_min_distance=100;
_f32 mouse_wheel_camera_unit=10;
_f32 auto_slow_down=0;
_f32 auto_slow_down_time=5000;
_f32 catom_connection_distance_cap_sq=100000;
_i32 num_undo_states=10;
_f32 catom_plane_force=0.1f;

#else if
extern uchar s_video_driver;
extern _f32 mousescale;
extern _f32 catom_positionscale;
extern _f32 catom_stepsize;
extern _f32 catom_numsteps;
extern _f32 catom_core_phi;
extern _f32 catom_core_exp;
extern _f32 catom_r_neutron;
extern _f32 catom_r_proton;
extern _f32 catom_core_away;
extern _f32 catom_elektron_startspeed;
extern _f32 catom_core_startforce;
extern _f32 catom_elektron_smoothvalue;
extern _f32 catom_core_coreforcescale;
extern bool catom_draw_elcoreline;
extern irr::core::vector3df sandboxsize;
extern _f32 catom_elektron_force;
extern _f32 catom_bank_coreforcescale;
extern _f32 catom_bank_force;
extern _f32 catom_bank_distance;
extern _f32 catom_connection_forcescale;
extern _f32 catom_inter_connection_forcescale;
extern _f32 catom_inter_connection_distance_multi;
extern _f32 catom_connection_backdrift;
extern _f32 catom_connection_backdrift_changing;
extern _f32 catom_connection_change_limit;
extern _f32 catom_connection_centerscale;
extern _f32 catom_connection_size;
extern _f32 catom_connection_length;
extern _f32 catom_connection_max_sensibility;
extern _f32 time_cap;
extern _f32 catom_connection2bank_force;
extern _f32 catom_connection2connection_force;
extern _f32 catom_banks_distance_cap;
extern _f32 catom_banks_near_distance_cap;
extern _f32 catom_bank2connection_force;
extern _i32 catom_change_cap;
extern _i32 catom_freezetime;
extern _f32 catom2catom_force_scale;
extern _f32 catom2catom_distance_cap;
extern _i32 catom_allow_freeze;
extern _f32 mouse_wheel_unit;
extern _f32 camera_default_distance;
extern _f32 camera_mouse_scale;
extern _f32 catom_connection_visible_distance;
extern _f32 catom_connection_transparent_distance;
extern _f32 camera_position_center_speed;
extern _f32 camera_target_center_speed;
extern _f32 camera_zoom_scale;
extern _f32 camera_zoom_min_distance;
extern _f32 mouse_wheel_camera_unit;
extern _f32 auto_slow_down;
extern _f32 auto_slow_down_time;
extern _f32 catom_connection_distance_cap_sq;
extern _i32 num_undo_states;
extern _f32 catom_plane_force;

#endif