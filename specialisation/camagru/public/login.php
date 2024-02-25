<?php
include_once 'header.php';
?>

	<section class="login-form">
		<h2>Log In</h2>
		<form action="includes/login.php" method="post"> <!-- Action is the file that will be executed when the form is submitted -->
			<input type="text" name="uid" placeholder="Username/Email...">
			<input type="password" name="pwd" placeholder="Password...">
			<button type="submit" name="submit">Log In</button>
		</form>
	</section>

<?php
include_once 'footer.php';
?>