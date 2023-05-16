#include "encabezados/FigurasXeometricas.hpp"
#include "encabezados/definicions.h"

#include <glad.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "encabezados/tiny_obj_loader.h"

#include <iostream>

FigurasXeometricas::FigurasXeometricas(int tipo) {
	this->tipo = tipo;
	// Debuxamos o tipo de figura (xeometrica, inimigo,...) que corresponda
	debuxar();
}

FigurasXeometricas::FigurasXeometricas(int tipo, std::string inputOBJfile) {
	this->tipo = tipo;
	cargarModelo(inputOBJfile);
	debuxaFiguraCargada();
}

FigurasXeometricas::~FigurasXeometricas() {
	glDeleteVertexArrays(1, VAO);
}

void FigurasXeometricas::debuxar() {
	// Neste caso so utilizaremos un VAO
	VAO = (unsigned int*)malloc(sizeof(unsigned int));

	switch (tipo) {
	case FIGURA_EIXOS:
		debuxaEixos();
		break;
	case FIGURA_CADRADO:
		debuxaCadrado();
		break;
	case FIGURA_CUBO:
		debuxaCubo();
		break;
	default:	// Por defecto debuxamos un cubo
		debuxaCubo();
		break;
	}
}

void FigurasXeometricas::renderizar() {
	switch (tipo) {
	case FIGURA_EIXOS:
		renderizarEixos();
		break;
	case FIGURA_CADRADO:
		renderizarCadrado();
		break;
	case FIGURA_CUBO:
		renderizarCubo();
		break;
	case FIGURA_CARGADA:
		renderizarFiguraCargada();
		break;
	}
}


void FigurasXeometricas::debuxaEixos() {
	unsigned int VBO, EBO;
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//Vertices          //Colores
		0.0f, 0.0f, 0.0f,	 1.0f, 1.0f, 1.0f,  // 0
		2.0f, 0.0f, 0.0f,	 0.0f, 1.0f, 1.0f, //x
		0.0f, 2.0f, 0.0f,	 1.0f, 0.0f, 1.0f,// y
		0.0f, 0.0f, 2.0f,	 1.0f, 1.0f, 0.0f, // z  
		2.0f ,2.0f, 2.0f,	 1.0f, 1.0f, 1.0f
	};
	unsigned int indices[] = {  // empieza desde cero
		0, 1,
		0, 2,
		0, 3,
		0, 4
	};

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position Color

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void FigurasXeometricas::renderizarEixos() {
	glBindVertexArray(*VAO);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
}

void FigurasXeometricas::debuxaCadrado() {
	unsigned int VBO;


	float vertices[] = {
		-0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,

		 -0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, .0f, 1.0f,  0.0f, 1.0f

	};

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Determinamos a posicion dos vertices no array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Determinamos a posicion das cores no array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Determinamos a posicion dos vectores normais no array
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Determinamos a posicion das texturas no array
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);

}

void FigurasXeometricas::renderizarCadrado() {
	glBindVertexArray(*VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FigurasXeometricas::debuxaCubo() {
	unsigned int VBO, EBO;

	float n = 0.577350f;	// Este valor es 1/sqrt(3)

	float vertices[] = {
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,  -n, -n, n,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,  n, -n, n,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,  n, n, n,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,1.0f,  -n, n, n,

		-0.5f, -0.5f,  -0.5f, 1.0f, 0.0f,0.0f,  -n, -n, -n,
		 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f,0.0f,  n, -n, -n,
		 0.5f,  0.5f,  -0.5f, 0.0f, 0.0f,1.0f,  n, n, -n,
		-0.5f,  0.5f,  -0.5f, 0.0f, 1.0f,1.0f,  -n, n, -n
	};

	unsigned int indices[] = {
		// Cara frontal
		0, 1, 2,
		0, 2, 3,

		// Cara de atrás
		4, 7, 6,
		4, 6, 5,

		// Cara superior
		2, 6, 3,
		3, 6, 7,

		// Cara inferior
		0, 4, 1,
		1, 4, 5,

		// Cara dereita
		1, 5, 2,
		5, 6, 2,

		// Cara esquerda
		0, 3, 4,
		4, 3, 7

	};

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// posicion vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// normais
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void FigurasXeometricas::renderizarCubo() {
	glBindVertexArray(*VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void FigurasXeometricas::cargarModelo(std::string inputOBJfile) {
	tinyobj::ObjReaderConfig reader_config;

	// Atopa a ultima aparicion do caracter '/'
	size_t posicionUltimaBarra = inputOBJfile.find_last_of('/');

	// Extrae a subcadea dende o inicio ata a posicion da ultima barra
	reader_config.mtl_search_path = inputOBJfile.substr(0, posicionUltimaBarra + 1);

	tinyobj::ObjReader reader;

	// No caso de que haxa erros
	if (!reader.ParseFromFile(inputOBJfile, reader_config)) {
		if (!reader.Error().empty()) {
			std::cerr << "TinyObjReader: " << reader.Error();
		}
		exit(EXIT_FAILURE);
	}

	// No caso de que haxa warnings
	if (!reader.Warning().empty()) {
		std::cout << "TinyObjReader: " << reader.Warning();
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
			int materialId = shapes[s].mesh.material_ids[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
				vertices[materialId].push_back(glm::vec3(vx, vy, vz));

				// Check if `normal_index` is zero or positive. negative = no normal data
				if (idx.normal_index >= 0) {
					tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
					tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
					tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];

					normais[materialId].push_back(glm::vec3(nx, ny, nz));
				}

				// Check if `texcoord_index` is zero or positive. negative = no texcoord data
				/*if (idx.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
				}*/

			}
			index_offset += fv;
		}
	}
}

void FigurasXeometricas::debuxaFiguraCargada() {
	// Reservamos memoria para debuxar as caras do obxecto unha a unha
	int numMateriais = vertices.size();

	VAO = (unsigned int*)malloc(numMateriais * sizeof(unsigned int));
	unsigned int* VBO = (unsigned int*)malloc(numMateriais * sizeof(unsigned int));
	unsigned int* NBO = (unsigned int*)malloc(numMateriais * sizeof(unsigned int)); // numNormais = numVertices

	// Declarar un iterador 
	std::map<int, std::vector<glm::vec3>>::iterator iterador;

	for (iterador = vertices.begin(); iterador != vertices.end(); ++iterador) {
		int idMaterial = iterador->first;
		std::vector<glm::vec3> verticesMaterial = iterador->second;
		std::vector<glm::vec3>normaisMaterial = normais[idMaterial];

		glGenVertexArrays(1, &VAO[idMaterial]);
		glBindVertexArray(VAO[idMaterial]);

		glGenBuffers(1, &VBO[idMaterial]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[idMaterial]);

		glBufferData(GL_ARRAY_BUFFER, verticesMaterial.size() * 3 * sizeof(tinyobj::real_t), &verticesMaterial[0], GL_STATIC_DRAW);
		
		// Determinamos a posicion dos vertices no array
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(tinyobj::real_t), (void*)0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &NBO[idMaterial]);
		glBindBuffer(GL_ARRAY_BUFFER, NBO[idMaterial]);
		glBufferData(GL_ARRAY_BUFFER, normaisMaterial.size() * 3 * sizeof(tinyobj::real_t), &normaisMaterial[0], GL_STATIC_DRAW);

		// Determinamos a posicion das normais no array
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(tinyobj::real_t), (void*)0);
		glEnableVertexAttribArray(2);
	}
}

void FigurasXeometricas::renderizarFiguraCargada() {

	for (std::map<int, std::vector<glm::vec3>>::iterator iter = vertices.begin();
		iter != vertices.end();
		++iter)
	{
		int idMaterial = iter->first;
		std::vector<glm::vec3> verticesMaterial = iter->second;

		glBindVertexArray(VAO[idMaterial]);
		glDrawArrays(GL_TRIANGLES, 0, verticesMaterial.size());
	}
}