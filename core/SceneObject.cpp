

using namespace std;

SceneObject::SceneObject(AbstractModel _model, Texture _texture, float _x, float _y, float _z, float _alpha, float _phi, float _a, float _b, float _c);
	~SceneObject();
	
	void move(Vector t);
	void rotate(float _alpha, float _phi);

	Vector getPosition();
	void setAttributes(Program* prog, int vLocation, int texCoordLocation, int modelLocation);
	void bindTexture();

	void draw();
