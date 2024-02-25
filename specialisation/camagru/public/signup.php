<?php
include_once 'header.php';
?>

	<section class="signup-form">
		<h2>Sign Up</h2>
		<form action="includes/signup.php" method="post"> <!-- Action is the file that will be executed when the form is submitted -->
			<input type="text" name="name" placeholder="Full name...">
			<input type="text" name="email" placeholder="Email...">
			<input type="text" name="uid" placeholder="Username...">
			<input type="password" name="pwd" placeholder="Password...">
			<button type="submit" name="submit">Sign Up</button>
		</form>
	</section>

<?php
include_once 'footer.php';
?>