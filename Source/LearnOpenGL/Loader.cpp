#include "Loader.h"
#include "glad/glad.h"

class RawModel* Loader::loadToVao(float vertices[], int size,unsigned int indexData[],int indexSize)
{
	unsigned int vaoID = createVao();
	bindIndexBuffer(indexData, indexSize);
	storeData2AttriList(0, vertices, size);  //  默认存储的是0号位置  
	unBindVao();
	RawModel* tmpModel = new RawModel(vaoID, indexSize /(/*3 * */sizeof(int)));
	models.push_back(tmpModel);
	return tmpModel;
}

void Loader::cleanUp()
{
	if (vaos.size() > 0)
	{
		glDeleteVertexArrays(vaos.size(),vaos.data());
	}

	if (vbos.size() > 0)
	{
		glDeleteVertexArrays(vbos.size(), vbos.data());
	}

	if (models.size() > 0)
	{
		for (auto it: models)
		{
			delete it;
		}
	}
}

unsigned int Loader::createVao()
{
	//初始化VAO
	unsigned int vaoID;
	glGenVertexArrays(1,&vaoID);
	//绑定VAO
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

void Loader::bindIndexBuffer(unsigned int indexBuffer[], int size)
{
	unsigned int iboID;
	glGenBuffers(1,&iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,indexBuffer, GL_STATIC_DRAW);
}

void Loader::unBindVao()
{
	//glBindVertexArray(0);
}

void Loader::storeData2AttriList(int index, float vertices[], int size)
{
	//把顶点数组复制到缓冲内存中供OpenGL使用
	unsigned int vboID;
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,size, vertices,GL_STATIC_DRAW);
	// 设置顶点属性指针  告诉OpenGL该如何解析顶点数据
	//glVertexAttribPointer(index,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//glBindBuffer(GL_ARRAY_BUFFER,0);
	vbos.push_back(vboID);

	glEnableVertexAttribArray(0);
}

