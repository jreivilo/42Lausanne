import { Injectable, CanActivate, ExecutionContext, SetMetadata } from '@nestjs/common';
import { HttpService } from '@nestjs/axios';
import { Observable, of } from 'rxjs';
import { map, catchError } from 'rxjs/operators';
import { Reflector } from '@nestjs/core';
import { JwtService } from '@nestjs/jwt';

export const IS_PUBLIC_KEY = 'isPublic';
export const Public = () => SetMetadata(IS_PUBLIC_KEY, true);

@Injectable()
export class AuthGuard implements CanActivate {
  constructor(private httpService: HttpService, private reflector: Reflector, private jwtservice: JwtService) {}
  
  canActivate(context: ExecutionContext): boolean | Promise<boolean> | Observable<boolean> {
      const request = context.switchToHttp().getRequest();
      const token = request.headers['authorization'];
      const isPublic = this.reflector.getAllAndOverride<boolean>(IS_PUBLIC_KEY, [
        context.getHandler(),
        context.getClass(),
      ]);

    if (isPublic){
      return true;
    }
    
    if (!token) {
      return false;
    }

    const tokenVerified = this.jwtservice.verify(token);

    return this.jwtservice.verifyAsync(token).then((decoded) => {
      request.user = decoded.sub;
      return true;
    }).catch((err) => {
      return false;
    });
  }
}