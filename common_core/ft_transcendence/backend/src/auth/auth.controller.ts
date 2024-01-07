import {
    Controller,
    Get,
    Query,
    Redirect,
    Res,
    Post,
    HttpStatus,
    Req,
    Logger,
    HttpCode,
    SetMetadata,
    UseGuards,
    Request,
    Patch,
    Body
} from '@nestjs/common';
import {AuthService} from './auth.service';
import {JwtAuthGuard} from './guard/jwt.guard';
import {decode} from 'jsonwebtoken';

export const IS_PUBLIC_KEY = 'isPublic';
export const Public = () => SetMetadata(IS_PUBLIC_KEY, true);

@Controller('auth')
export class AuthController {
    constructor(private readonly authService: AuthService) {
    }

    @Public()
    @Get('login')
    @Redirect()
    login(): { url: string } {
        const queryParams = {
            client_id: this.authService.getClientId(),
            redirect_uri: this.authService.getRedirectUri(),
            response_type: 'code',
        };
        return {url: `https://api.intra.42.fr/oauth/authorize?${new URLSearchParams(queryParams)}`};
    }

    @Public()
    @Get('callback')
    @HttpCode(200)
    async callback(@Query('code') code: string, @Res({passthrough: true}) res: Response): Promise<{
        token: null
    }> {
        const token = await this.authService.exchangeCodeForToken(code);

        const me = await this.authService.getMeInfo(token.access_token);
        let user = await this.authService.fetchUserByLogin(me.login);
        if (!user) {
            user = await this.authService.createUser(me);
        }

        // 2FA verify
        if (user.twofactor) {
            return {token: await this.authService.getJwtToken(user.id.toString(), user.twofactor.toString())};
        }

        return {token: await this.authService.getJwtToken(user.id.toString(), user.twofactor.toString())};
    }

    @Get('2fa/qrcode')
    @UseGuards(JwtAuthGuard)
    async getQRCode(@Request() req) {
        // const secret = await this.authService.enable2FA(req.user.id.toString());
        const otpauth = await this.authService.generateQRCode(parseInt(req.user.id));
        return {otpauth};
    }

    @Patch('2fa/verify')
    @UseGuards(JwtAuthGuard)
    async verify2FA(@Request() req, @Body('code') code: string): Promise<{
        isValid: boolean,
        token: string
    }> {
        const userId = parseInt(req.user.id);

        const isValid = await this.authService.verify2FA(userId, code);
        // If isValid change token twofactor to valid
        if (isValid) {
            this.authService.enable2FA(userId);
            return {isValid, token: await this.authService.getJwtToken(userId, "valid")};
        }
        return {isValid, token: null};
    }

    @Get('token/valid')
    @UseGuards(JwtAuthGuard)
    async checkTokenValidity(@Request() req) {
        try {
            // Access the token from the "Authorization" header
            const token = req.headers.authorization.replace('Bearer ', '');

            // Now, you can pass the token to your authService to check its validity
            const res = await this.authService.checkTokenValidity(token);
            return {res};
        } catch (error) {
            // Handle errors, such as invalid token format or token validation failure
            console.error(error);
            return {error};
        }
    }

    @Patch('2fa/enable')
    @UseGuards(JwtAuthGuard)
    async activate2FA(@Request() req) {
        const res = await this.authService.enable2FA(parseInt(req.user.id));
    }

    @Patch('2fa/disable')
    @UseGuards(JwtAuthGuard)
    async deactivate2FA(@Request() req) {
        const res = await this.authService.disable2FA(parseInt(req.user.id));
    }
}
