#include <irrlicht.h>
#include "KornJungle/Jungle.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char** argv)
{

    IrrlichtDevice *device =
        createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 16,
            false, false, false, 0);

    device->setWindowCaption(L"Jungle Generator");

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    // camera
    ICameraSceneNode* camera =
        smgr->addCameraSceneNodeFPS(0,100.0f,1.2f);

    // terrain
    ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
        "./media/terrain-heightmap.bmp",
        0,                  // parent node
        -1,                 // node id
        core::vector3df(0.f, 0.f, 0.f),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(40.f, 4.4f, 40.f),  // scale
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,             // patchSize
        4                   // smoothFactor
        );

    terrain->setMaterialFlag(video::EMF_LIGHTING, false);

    terrain->setMaterialTexture(0,
            driver->getTexture("./media/terrain-texture.jpg"));
    terrain->setMaterialTexture(1,
            driver->getTexture("./media/detailmap3.jpg"));

    terrain->setMaterialType(video::EMT_DETAIL_MAP);

    terrain->scaleTexture(1.0f, 20.0f);

    // create jungle.
    // terrain is 256 x256
    // lets create density of one tree every 8x8 pixel
    jungleScene::Jungle *jungle =
        new jungleScene::Jungle(
                10240, // world size
                8,// chunk size. "chunk size" * "chunk size" = "tree count per chunk"
                16,// max tree dimension diameter
                4,// tree circular detail
                terrain,
                smgr,
                -1);
    smgr->getRootSceneNode()->addChild(jungle);
    jungle->getMaterial(0).setFlag(EMF_LIGHTING, false);
    //jungle->getMaterial(0).setFlag(EMF_BACK_FACE_CULLING, false);
    jungle->getMaterial(0).setTexture(0, driver->getTexture("./media/bark.png"));
    jungle->getMaterial(0).MaterialType = EMT_SOLID;

    jungle->getMaterial(1).setFlag(EMF_LIGHTING, false);
    jungle->getMaterial(1).setFlag(EMF_BACK_FACE_CULLING, false);
    jungle->getMaterial(1).setTexture(0,driver->getTexture("./media/leaf.png"));
    jungle->getMaterial(1).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL_REF;


    // start growing trees
    for(u32 i = 0 ; i < 5000 ; i++)
    {
        f32 cx = 100.0f + rand()%10040;
        f32 cy = 100.0f + rand()%10040;
        int type = rand()%8+1;
        int seed = rand();
        //trees
        switch(type)
        {
            case(1):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    16,// segment
                    5,// min rot
                    30,// max rot
                    800.0f, // length
                    2, // branching count
                    7.5f, // max radius;
                    3, // ground root
                    200.0f, // leaf_width
                    200.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    0, //leaf type
                    0, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(2):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    25,// segment
                    0,// min rot
                    15,// max rot
                    800.0f, // length
                    4, // branching count
                    25.0f, // max radius;
                    4, // ground root
                    400.0f, // leaf_width
                    400.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    1, //leaf type
                    1, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(3):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    32,// segment
                    0,// min rot
                    15,// max rot
                    400.0f, // length
                    4, // branching count
                    5.0f, // max radius;
                    3, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    2, //leaf type
                    2, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(4):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    32,// segment
                    5,// min rot
                    20,// max rot
                    400.0f, // length
                    4, // branching count
                    20.0f, // max radius;
                    4, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    3, //leaf type
                    3, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(5):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    12,// segment
                    10,// min rot
                    20,// max rot
                    400.0f, // length
                    4, // branching count
                    7.5f, // max radius;
                    3, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    4, //leaf type
                    4, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(6):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    12,// segment
                    15,// min rot
                    20,// max rot
                    400.0f, // length
                    4, // branching count
                    5.0f, // max radius;
                    3, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    5, //leaf type
                    5, // bark type
                    seed, // seed
                    true
                   );
                break;
            }
            case(7):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    14,// segment
                    4,// min rot
                    20,// max rot
                    400.0f, // length
                    4, // branching count
                    10.0f, // max radius;
                    3, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    6, //leaf type
                    6, // bark type
                    seed, // seed
                    true
                   );
                break;
            }
            case(8):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                   20,// segment
                   0,// min rot
                   30,// max rot
                   400.0f, // length
                   4, // branching count
                   10.0f, // max radius;
                   3, // ground root
                   200.0f, // leaf_width
                   200.0f, // leaf height
                   2, // leaf segments
                   1.0, // leaf stiffness
                   7, //leaf type
                   7, // bark type
                   seed, // seed
                    true
                   );
                    break;
            }
        }
    }

     while(device->run())
    {
        driver->beginScene(true, true, SColor(0,200,200,200));
        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

    device->drop();

    return 0;
}

