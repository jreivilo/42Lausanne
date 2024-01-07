import { Controller, Get, Res, UseGuards } from '@nestjs/common';
import { Response } from 'express';
import { AppService } from './app.service';
import { AuthGuard } from './auth/auth.guard';

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get()
  getHello(@Res() res: Response): void {
    res.send(`
      <h1>Welcome to My App</h1>
      <p>${this.appService.getHello()}</p>
      <a href="/api/auth/login">Sign In with 42</a>
    `);
  }

  @Get('protected')
  @UseGuards(AuthGuard)
  getProtected(@Res() res: Response): void {
	res.send(`
	  <h1>Protected Route</h1>
	  <p>This route is protected by AuthGuard</p>
	  <a href="/users">Users</a>
    <a href="/">Home</a>
	`);
  }
}