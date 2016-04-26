

using namespace std;

SceneObject::SceneObject(AbstractModel _model, Texture _texture, float _x, float _y, float _z, float _alpha, float _phi, float _a, float _b, float _c) 
{
}

SceneObject::~SceneObject()
{
}
	
void SceneObject::move(Vector t) 
{
}

void SceneObject::rotate(float _alpha, float _phi) 
{
}

Vector SceneObject::getPosition() 
{
}

void SceneObject::setAttributes(Program* prog, int vLocation, int texCoordLocation, int modelLocation) 
{
}

void SceneObject::bindTexture() 
{
}

void SceneObject::draw()
{
}
