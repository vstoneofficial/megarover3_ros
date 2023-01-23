#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


class MouseReceiver
{
public:
  MouseReceiver();

private:
  void twistCallback(const geometry_msgs::Twist::ConstPtr& mouse);

  ros::NodeHandle nh_;

  ros::Publisher vel_pub_;
  ros::Subscriber mouse_sub_;

};


MouseReceiver::MouseReceiver()
{

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("rover_twist", 1);


  mouse_sub_ = nh_.subscribe<geometry_msgs::Twist>("mouse_vel", 1, &MouseReceiver::twistCallback, this);

}

void MouseReceiver::twistCallback(const geometry_msgs::Twist::ConstPtr& mouse)
{
  geometry_msgs::Twist twist;
  twist.angular.z = mouse->angular.z;
  twist.linear.x = mouse->linear.x;
  twist.linear.y = mouse->linear.y;

  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "mouse_receiver");
  MouseReceiver mouseReceiver;

  ros::NodeHandle n;

  ros::Rate r(10);
  while(n.ok()){
    ros::spinOnce();
    r.sleep();
  }
}
