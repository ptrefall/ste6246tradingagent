#pragma once

#include <Irrlicht\irrlicht.h>
#include <Windows.h>
#include <unordered_map>
namespace irr
{
	namespace scene
	{

	//Direction of this sprite
	enum SpriteForwardDirection
	{
		ESD_NORTH,
		ESD_EAST,
		ESD_SOUTH,
		ESD_WEST,
		ESD_COUNT
	};

	//Which face of this sprite to display
	enum SpriteFace
	{
		ESF_FRONT,
		ESF_BACK,
		ESF_LEFT,
		ESF_RIGHT,
		ESF_COUNT
	};

	//Which order of sequence an animation should be played
	struct SpriteAnimSequence
	{
		std::vector<s32> seq;
		s32 crntIndex;

		SpriteAnimSequence() : crntIndex(-1) {}
		SpriteAnimSequence(const std::vector<s32> &seq) : seq(seq), crntIndex(-1) {}
		SpriteAnimSequence(const s32 &v0, const s32 &v1, const s32 &v2, const s32 &v3) : crntIndex(-1) { seq.push_back(v0); seq.push_back(v1); seq.push_back(v2); seq.push_back(v3); }
		void update() { crntIndex++; if((u32)crntIndex >= seq.size()) crntIndex = 0;}
		void reset() { crntIndex = -1; }
		s32 currentFrame() { if(crntIndex < 0) return 0; return seq[crntIndex]; }
	};

	struct SpriteAnimState
	{
		SpriteFace face;
		SpriteAnimSequence seq;
		
		SpriteAnimState() : face(ESF_BACK) {}
		SpriteAnimState(const SpriteFace &face, const SpriteAnimSequence &seq) : face(face), seq(seq) {}
		void reset() { seq.reset(); }
		void update() { seq.update(); }
		s32 currentFrame() { return seq.currentFrame(); }
	};

	class TAnimSprite : public ISceneNode
	  {
		 private:
			   core::aabbox3d<f32> Box; 
			   video::S3DVertex    Vertices[4];
			   u16                 Indices[12]; 
			   video::SMaterial    Material; 
			   video::ITexture*    Texture;
			   f32                 fWidth,fHeight;
			   s32                 crntFrm,TotalFrm;
			   s32                 stepww,stephh;
			   typedef std::unordered_map<SpriteForwardDirection, SpriteAnimState> SpriteDirectionStateMap;
			   SpriteDirectionStateMap spriteDirectionStates;
			   SpriteForwardDirection currentDirectionState;
			   BOOL                forward;
			   DWORD               time;
			   DWORD               oldtick;
           
           
		  public: 
			  TAnimSprite(ISceneNode* parent, ISceneManager* mgr, s32 id): ISceneNode(parent, mgr, id)
			   {      
					  Material.Wireframe = false;
					  Material.Lighting = false;
                  
					  u16 ind[] = { 0,1,3, 3,1,2, 1,0,2, 2,0,3 };
					  memcpy(Indices,ind,sizeof(u16)*12);     

					  spriteDirectionStates[ESD_NORTH] = SpriteAnimState(ESF_BACK,  SpriteAnimSequence(0, 2, 0, 2));
					  spriteDirectionStates[ESD_EAST]  = SpriteAnimState(ESF_RIGHT, SpriteAnimSequence(3, 5, 3, 5));
					  spriteDirectionStates[ESD_SOUTH] = SpriteAnimState(ESF_FRONT, SpriteAnimSequence(6, 8, 6, 8));
					  spriteDirectionStates[ESD_WEST]  = SpriteAnimState(ESF_LEFT,  SpriteAnimSequence(9, 11, 9, 11));
					  currentDirectionState = ESD_SOUTH;
			   }     
          
			  virtual void Load(const char* filename, s32 frmWidth, s32 frmHeight)
			   {
				   video::IVideoDriver* driver = SceneManager->getVideoDriver();
				   core::dimension2d<u32> Screensize = driver->getScreenSize(); 
				   float x = (float)frmWidth/(float)Screensize.Width;
				   float y = (float)frmHeight/(float)Screensize.Height;
				   Vertices[0] = video::S3DVertex(-x, 0,  0, 0,0,0,video::SColor(255,255,255,255),0,1);
				   Vertices[1] = video::S3DVertex( x, 0,  0, 0,0,0,video::SColor(255,255,255,255),1,1); 
				   Vertices[2] = video::S3DVertex( x, 2*y,0, 0,0,0,video::SColor(255,255,255,255),1,0);
				   Vertices[3] = video::S3DVertex(-x, 2*y,0, 0,0,0,video::SColor(255,255,255,255),0,0);
               
				   Box.reset(Vertices[0].Pos);
				   for (s32 i=1; i<4; ++i)  
					   Box.addInternalPoint(Vertices[i].Pos);
                  
				   Texture = driver->getTexture(filename);
				   driver->makeColorKeyTexture(Texture,core::position2d<s32>(0,0));
                
				   Material.TextureLayer[0].Texture = Texture;
				   Material.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
				   Material.ZWriteEnable = true;
               
				   core::dimension2d<u32> size = Texture->getOriginalSize();
				   fWidth  = (float)frmWidth/(float)size.Width;
				   fHeight = (float)frmHeight/(float)size.Height;
				   crntFrm = 0;
				   stepww = size.Width / frmWidth;
				   stephh = size.Height / frmHeight;
				   TotalFrm = stepww * stephh;
				   forward = TRUE;
                             
				   Vertices[0].TCoords.X = 0; 
				   Vertices[0].TCoords.Y = fHeight;
				   Vertices[1].TCoords.X = fWidth; 
				   Vertices[1].TCoords.Y = fHeight;
				   Vertices[2].TCoords.X = fWidth; 
				   Vertices[2].TCoords.Y = 0;
				   Vertices[3].TCoords.X = 0; 
				   Vertices[3].TCoords.Y = 0;
			   }
           
			  virtual void PlayForward() {forward = TRUE;}
			  virtual void PlayBackward() {forward = FALSE;} 
			  virtual void SetSpeed(int spd)  {time = spd;}
           
			  virtual void OnRegisterSceneNode()
			   { 
				  if (IsVisible)
				  {
					  SceneManager->registerNodeForRendering(this);
					  ISceneNode::OnRegisterSceneNode();
				  }
			   }
           
			  virtual void setFrame(int n)
			   {
				   float x = (n % stepww)*fWidth;
				   float y = (n / stepww)*fHeight; 
				   Vertices[0].TCoords.X = x; 
				   Vertices[0].TCoords.Y = y+fHeight;
				   Vertices[1].TCoords.X = x+fWidth; 
				   Vertices[1].TCoords.Y = y+fHeight;
				   Vertices[2].TCoords.X = x+fWidth; 
				   Vertices[2].TCoords.Y = y;
				   Vertices[3].TCoords.X = x; 
				   Vertices[3].TCoords.Y = y;
               
			   }
          
			  virtual void Update(const SpriteForwardDirection &direction)
			   {
				  if(GetTickCount()-oldtick > time)
				  {  
					   oldtick = GetTickCount();
					   /*if (forward) 
					   {
						   crntFrm++; 
						   if (crntFrm > TotalFrm-1)crntFrm = 0;
					   }
					   else
					   {
						   crntFrm--;
						   if (crntFrm < 0 )crntFrm = TotalFrm-1;
					   }      
					   float x = (crntFrm % stepww)*fWidth;
					   float y = (crntFrm / stepww)*fHeight; */

					   float x,y;
					   if(currentDirectionState == direction)
					   {
							SpriteDirectionStateMap::iterator anim_state_it = spriteDirectionStates.find(direction);
							SpriteAnimState &anim_state = anim_state_it->second;
							anim_state.update();
							x = (anim_state.currentFrame() % stepww)*fWidth;
							y = (anim_state.currentFrame() / stepww)*fHeight;
					   }
					   else
					   {
						   {
								SpriteDirectionStateMap::iterator anim_state_it = spriteDirectionStates.find(currentDirectionState);
								SpriteAnimState &anim_state = anim_state_it->second;
								anim_state.reset();
								currentDirectionState = direction;
						   }

						   {
								SpriteDirectionStateMap::iterator anim_state_it = spriteDirectionStates.find(direction);
								SpriteAnimState &anim_state = anim_state_it->second;
								anim_state.update();
								x = (anim_state.currentFrame() % stepww)*fWidth;
								y = (anim_state.currentFrame() / stepww)*fHeight;
						   }
					   }

					   Vertices[0].TCoords.X = x; 
					   Vertices[0].TCoords.Y = y+fHeight;
					   Vertices[1].TCoords.X = x+fWidth; 
					   Vertices[1].TCoords.Y = y+fHeight;
					   Vertices[2].TCoords.X = x+fWidth; 
					   Vertices[2].TCoords.Y = y;
					   Vertices[3].TCoords.X = x; 
					   Vertices[3].TCoords.Y = y;
				  }     
			   }     
          
			  virtual s32 GetMaxFrames() { return TotalFrm; }
            
			  virtual void render()
			   {  
				   /*this->updateAbsolutePosition();
				   core::vector3df vect = (getSceneManager()->getActiveCamera()->getAbsolutePosition()) - (this->getAbsolutePosition());
					vect = vect.getHorizontalAngle();
					std::cout << vect.Y << " ";
					//vect.Y = -vect.Y;
					//vect.Z = 0;
					vect.X = 0;
					this->setRotation(vect);*/
               
				  video::IVideoDriver* driver = SceneManager->getVideoDriver();
				  driver->setMaterial(Material);  
				  core::matrix4 Trns,Scl,Rot,wrld;
				  Trns.makeIdentity(); 
				  Scl.makeIdentity();
				  Rot.makeIdentity();
				  Trns.setTranslation(RelativeTranslation);
				  Scl.setScale(RelativeScale);
				  Rot.setRotationRadians(RelativeRotation);
				  wrld = Trns * Rot * Scl;
				  driver->setTransform(video::ETS_WORLD, wrld);
				  driver->drawIndexedTriangleList(&Vertices[0], 4, &Indices[0], 4);
			   }

			  virtual const core::aabbox3d<f32>& getBoundingBox() const 
			   { 
				  return Box; 
			   }
  
			  virtual s32 getMaterialCount()
			   {
				  return 1;
			   }
  
			  virtual video::SMaterial& getMaterial(s32 i)
			   {
				 return Material;
			   } 
           
	  }; 
	}
}