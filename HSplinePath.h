#pragma once
#include "SplineSample.h"
#include "HSplineCore.h"

namespace HSSSpline
{
    class HSpline2D: public HSplineCore<2>
    {
    protected:
        PathPoints<2> m_Piecewise_Points;//��l��J�I
        PathPoints<2> m_Ctrl_Points;     //�����I
        vector<float> m_CtrlPoines;         // Ctrl Points ����I
        vector<float> m_Cubic_Spline;       // Cubic_Spline data(2D)
        vector<float> m_Cubic_Spline_Depth; // Cubic_Spline + depth(3D)
        int mode; //0 is front view(on z plane), 1 is left view(on x plane)
        float const_number; // if mode is 0, set const_number to 0.29. if mode is 1, set const_number to -0.5

    public:
        void Clean(){
            m_Piecewise_Points().clear();
            m_CtrlPoines.clear();
            m_Cubic_Spline.clear();
            m_Cubic_Spline_Depth.clear();
        }

        void PushBack(PathPoint<2>& posn);

        void AssignPoints(PathPoints<2>& points);
        PathPoints<2> GetPiecewisePoints(){return m_Piecewise_Points;}

        const PathPoint<2>& GetCtrlPoint(int idx){return m_Ctrl_Points[idx];}
        PathPoints<2>       GetCtrlPoints(){return m_Ctrl_Points;}
        virtual void	 AssignCtrlPoints(PathPoints<2>& ctrl_points);
        void			 AugmentCtrlPoint(int num);

        PathPoint<2> Begin(){return m_Ctrl_Points().front();}
        PathPoint<2> End(){return m_Ctrl_Points().back();}

    //GetInfo
    public:
        /*���ospline�W���Y�@�I��m, seg�O���@�q, t�O�Ѽ�*/
        PathPoint<2>    get_position(int _seg, double _t);
        PathPoint<2>    get_position(const Sample& sample){return get_position(sample.seg_idx,sample._t);}
        /*���ospline�W���Y�@�I���u, seg�O���@�q, t�O�Ѽ�*/
        PathPoint<2> get_tangent(int _seg, double _t);
        PathPoint<2> get_tangent(const Sample& sample){return get_tangent(sample.seg_idx,sample._t);}
        /*���ospline�W���Y�@�I�k�V�q, seg�O���@�q, t�O�Ѽ�*/
        PathPoint<2> get_normal(int _seg, double _t);
        PathPoint<2> get_normal(const Sample& sample){return get_normal(sample.seg_idx,sample._t);}

        /*���y�Ф��q*/
        double get_x(int _seg, double _t){return get_value(0,_seg,_t);}
        double get_y(int _seg, double _t){return get_value(1,_seg,_t);}

    //Editting
    public:
        double  SelectCtrlPoint(double x,double y,int *select);//�^�ǳ̵u�Z���ASelect����쪺�I
        //�s��Ctrl Point��m
        virtual void EditCtrlPoint(int c_id,PathPoint<2>& point);

    //Sampling
    public:
        //�qpixel����
        void    FittingCurve(double fit_ratio,bool auto_adjust = true);//   1 / Fit Ratio = �Ϭq��
        //�q�ثecurve����
        void    RefittingCurve(double fit_ratio);

        Samples        UniformSampling(double per_len);
        PathPoints<2>  GetUniformSamplePoints(double per_len);

    //���׭p��
    public:
        double Lenght();
        double BeginToSampleLenght(const Sample& s);
        double SampleToEndLenght(const Sample& s);
        double Lenght(const Sample& s0,const Sample& s1);

    protected:
        double SegLenght(int seg_idx);
        double SegToSampleLenght(const Sample& sample);

    //Shift
    public:
        bool ShiftSample(Sample& from,double offset,Sample*  output);
        bool ShiftSampleForeward(Sample& from,double offset,Sample*  output);
        bool ShiftSampleBackward(Sample& from,double offset,Sample*  output);

    //Rendering
    public:
        void DrawLine();
        void DrawLine(Sample& from,Sample& to);
        void DrawCtrlPoint();

    //Shader
    public:
        void PushCtrlPoint();
        void PushCubicSplined_init();
        void PushCubicSplined(Sample& from,Sample& to);
        vector<float> Get_CtrlPoint(){return m_CtrlPoines;}
        vector<float> Get_Cubic_Splilne(){return m_Cubic_Spline;}
        vector<float> Get_Cubic_Spline_depth(){return m_Cubic_Spline_Depth;}
    };
}
