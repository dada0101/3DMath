/////////////////////////////////////////////////////////////////////
//
//3D Math Primer for Graphics and Game Development
//
//EditTriMesh.h - Declarations for class EditTriMesh
//
//For more details, see EditTriMesh.cpp
//
/////////////////////////////////////////////////////////////////////

#ifndef EDITTRIMESH_H_INCLUDED
#define EDITTRIMESH_H_INCLUDED

#ifndef VECTOR_H_INCLUDED
#include "Vector3.h"
#endif // VECTOR_H_INCLUDED


class Matrix4x3;
/////////////////////////////////////////////////////////////////////
//
//EditTriMesh��
//��һ�ַǳ����ĸ�ʽ����������������
//ʹ������༭�Ͳ�������ʵ�֣�δ����Ⱦ����ײ��⣬�������������Ż���
//֧������ӳ������Ͷ��㷨����
//
/////////////////////////////////////////////////////////////////////
class EditTriMesh
{
public:
    //�ֲ�����
    //Vertex�����ڱ��涥����Ϣ
    class Vertex
    {
    public:
        Vertex() {setDefaults();}
        void setDefaults();
        //3D����
        Vector3 p;
        //���㼶����ӳ������
        //ע����Щ����ֵ������ʧЧ��������UV���걣������������
        //������Ⱦ��������Ҫ���㼶����������
        //���������Ż���������Ҫ���Ӳ�ͬUVֵ�Ķ���
        float u, v;
        //���㼶���淨������ͬ������ʧЧ
        Vector3 normal;
        //���߱������ܷ���
        int mark;
    };
    //��Tri���ڱ�����������Ϣ
    class Tri
    {
    public:
        Tri() {setDefaults();}
        void setDefaults();
        //�涥��
        struct Vert
        {
            int index;      //�����б������
            float u, v;     //��������
        };

        Vert v[3];
        //���淨����
        Vector3 normal;
        //����������Ĳ��֣�
        int part;
        //�����б�����
        int material;
        //���߱���������
        int mark;
        //�ж��Ƿ�Ϊ�˻�������-ͬһ����ʹ�ó���һ��
        bool isDegenerate() const;
        //���ض���������0..2����-1�����δʹ�øö���
        int findVertex(int vertexIndex) const;
    };
    //���������Ϣ
    //����ֻ����һ���򵥵�����������ӳ��
    //���ʾ��������������ӵ���Ϣ
    class Material
    {
    public:
        Material() {setDefaults();}
        void setDefaults();
        char diffuseTextureName[256];
        //���߱���
        int mark;
    };
    //�����Ż���ѡ��
    class OptimationParameters
    {
        OptimationParameters() {setDefaults();}
        void setDefaults();
        //�ж����������Ƿ��غϵ��ݲ�
        float coincidentVertexTolerance;
        //�����νǶ��ݲ�
        //���������ĳһ�߱���ͬ����������������Щ�����η������ǶȺܴ�
        //��ô�����������ϵĶ��㲻�ܱ�����
        //�������Ǳ�������Ƕȵ�cosֵ�����������������������
        float cosOfEdgeAngleTolerance;
        void setEdgeAngleToleranceInDegrees(float degrees);
    };
    //��׼�����
    EditTriMesh();
    EditTriMesh(const EditTriMesh &x);
    ~EditTriMesh();
    //=����������������
    EditTriMesh &operator=(const EditTriMesh &src);
    //��ȡ��������
    int vertexCount() const {return vCount;}

    int triCount() const {return tCount;}

    int materialCount() const {return mCount;}

    Vertex &vertex(int vertexIndex);
    const Vertex &Vertex(int vertexIndex) const;
    Material &material(int materialIndex);

    const Matetrial &material(int materialIndex) const;
    //�����������
    //��������Ϊ��
    void empty();
    //�����б�Ϊ��
    //����б������������ӵ�ֵ���к��ʵĳ�ֵ
    //����б����������������Ч�Լ��
    void setVertexCount(int vc);
    void setTriCount(int to);
    void setMaterialCount(int mc);
    //���������/����/���ʣ������¼���Ԫ�ص�����
    int addTri();
    int addTri(const Tri &t);
    int addVertex();
    int addVertex(const Vertex &v);
    int dupVertex(int srcVertexIndex);
    int addMatetial(const Material &m);
    //ͬʱ��������mark����
    void markAllVertices(int mark);
    void markAllTris(int mark);
    void markAllMaterials(int mark);
    //ɾ������
    void deleteVertex(int vertexIndex);
    void deleteTri(int triIndex);
    void deleteMaterial(int materialIndex);
    void deleteUnusedMaterials();
    void deleteMarkedTris(int mark);
    void deleteDegenerateTris();
    //�������������
    //������������һ���µĶ����б�
    //����ÿ������ֻ����һ��������
    //ͬʱɾ��δ�õĵ�
    void detachAllFaces();
    //�任���ж���
    void transformVertices(const Matrix4x3 &m);
    //����
    //���������εı��淨����
    void computeOneTriNormal(int triIndex);
    void computeOneTriNormal(Tri &t);
    void computeTriNormals();
    //���㶥�㷨�������Զ����������η�����
    void computeVertexNormals();
    //�Ż�
    //����ʹ������������ж����б��ܹ���ǿcache������
    //����ɾ��δ�õĶ���
    void optimizeVertexOrder(bool removeUnusedVertices);
    //���ݲ���Ϊ���������򣬶��ڿ�����Ⱦ�ǳ���Ҫ
    void sorkTrisByMaterial();
    //���Ӷ���
    void weldVertices(const OptimationParameters &opt);
    //ȷ������UVֵ��ȷ�������Ҫ���ܻḴ�ƶ���
    void copyUvsIntoVertices();
    //�������е��Ż���Ϊ������Ⱦ׼����ģ�ͣ����й��գ����ڴ������Ⱦϵͳ��˵
    void optimizeForRendering();
    //����/����S3Dģ��
    bool importS3d(const char *filename, char *returnErrMsg);
    bool exportS3d(const char *filename, char *returnErrMsg);
    //������
    void validityCheck();
    void validityCheck(char *returnErrMsg);
private:
    //�����б�
    int vAlloc;
    int vCount;
    Vertex *vList;
    int tAlloc;
    int tCount;
    Tri *tList;
    int mCount;
    Material *mList;
    //ʵ��ϸ��
    void construct();
};
/////////////////////////////////////////////////////////////////////
#endif // EDITTRIMESH_H_INCLUDED
