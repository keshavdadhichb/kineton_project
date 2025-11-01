from django.contrib import admin
from django.urls import path, include
from django.conf import settings
from django.conf.urls.static import static

# --- DRF Spectacular imports ---
from drf_spectacular.views import SpectacularAPIView, SpectacularSwaggerView
from drf_spectacular.utils import extend_schema

# --- Google Login imports ---
from dj_rest_auth.registration.views import SocialLoginView
from allauth.socialaccount.providers.google.views import GoogleOAuth2Adapter
from allauth.socialaccount.providers.oauth2.client import OAuth2Client


# --- Google Login View ---
@extend_schema(exclude=True)  # Exclude from Swagger docs to prevent AttributeError
class GoogleLogin(SocialLoginView):
    adapter_class = GoogleOAuth2Adapter
    callback_url = "http://127.0.0.1:8000/api/auth/google/callback/"
    client_class = OAuth2Client


# --- URL Patterns ---
urlpatterns = [
    path('admin/', admin.site.urls),

    # Frontend / Monolith URLs
    path('', include('dashboard.urls')),
    path('accounts/', include('allauth.urls')),

    # API (DRF) URLs
    path('api/v1/', include('api.urls')),
    path('api/auth/', include('dj_rest_auth.urls')),
    path('api/auth/registration/', include('dj_rest_auth.registration.urls')),
    path('api/auth/google/', GoogleLogin.as_view(), name='google_login_api'),

    # API Schema and Docs
    path('api/schema/', SpectacularAPIView.as_view(), name='schema'),
    path('api/docs/', SpectacularSwaggerView.as_view(url_name='schema'), name='swagger-ui'),
]


# --- Media files serving during development ---
if settings.DEBUG:
    urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
