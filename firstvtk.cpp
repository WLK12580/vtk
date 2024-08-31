#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

int main(int argc, char const *argv[])
{
	//创建vtkNamedColors对象为背景和对象选择颜色
	vtkNew<vtkNamedColors> color;

	//创建VTKConeSource实例，并设置其属性
	vtkNew<vtkConeSource> cone;
	cone->SetHeight(3); //设置高度
	cone->SetRadius(1); //设置半径
	cone->SetResolution(100); //设置分辨率

	//创建vtkPolyDataMapper 实例，将多边形数据映射到图形基元中
	vtkNew<vtkPolyDataMapper> coneMapper;
	coneMapper->SetInputConnection(cone->GetOutputPort());

	//创建一个对象来负责cone

	vtkNew<vtkActor> actorCone;
	actorCone->SetMapper(coneMapper);
	actorCone->GetProperty()->SetColor(color->GetColor3d("MistyRose").GetData()); //设置颜色

	//创建渲染器
	vtkNew<vtkRenderer> render;
	render->AddActor(actorCone);
	render->SetBackground(color->GetColor3d("MidnightBlue").GetData());

	//创建渲染窗口显示
	vtkNew<vtkRenderWindow> win;
	win->AddRenderer(render);
	win->SetSize(100,200);
	win->SetWindowName("cone");

	for (int i = 0; i < 36000; ++i)
  {
    // Render the image
    win->Render();
    // Rotate the active camera by one degree.
    render->GetActiveCamera()->Azimuth(0.01);
	
  }
  return EXIT_SUCCESS;
}
