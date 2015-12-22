<?php 
$output .= '<form name="login_form" method="post" action="'.$data['action'].'">';
$output .= '<p>  ';
$output .= '<label for="username" class="label">用户名:</label>  ';
$output .= '<input id="username" name="username" type="text" class="input" />  ';
$output .= '<p/>  ';
$output .= '<p>  ';
$output .= '<label for="password" class="label">密&nbsp;&nbsp;&nbsp;码:</label>  ';
$output .= '<input id="password" name="password" type="password" class="input" />  ';
$output .= '<p/>  ';
$output .= '<p>  ';
$output .= '<input type="submit" name="submit" value="  确 定  " class="left" />  ';
$output .= '</p>  ';
$output .= '</form> ';

?>